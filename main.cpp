#pragma optimize("", on)
#include <iostream>
#include "binary.hpp"
#include "vm.hpp"

using namespace llvm;

#define IMAGE 0x140000000

int main()
{
	std::string input_file = "input.exe";
	uint64_t routine_va = 0x140017A41;

	std::unique_ptr<LIEF::PE::Binary> binary = LIEF::PE::Parser::parse(input_file);
	if (!binary) {
		std::cerr << "[!] Failed to load PE file!" << std::endl;
		return -1;
	}

	auto routine_content = binary->get_content_from_virtual_address(routine_va, 10);
	auto vm_entry_disassembly = disassemble(routine_content, routine_va, ZYDIS_MNEMONIC_JMP);

	if (vm_entry_disassembly[0].i.mnemonic != ZYDIS_MNEMONIC_PUSH || vm_entry_disassembly[0].operands[0].type != ZYDIS_OPERAND_TYPE_IMMEDIATE ||
		vm_entry_disassembly[1].i.mnemonic != ZYDIS_MNEMONIC_JMP || vm_entry_disassembly[1].operands[0].type != ZYDIS_OPERAND_TYPE_IMMEDIATE ||
		vm_entry_disassembly[1].operands[0].imm.is_relative == false)
	{
		return -1;
	}

	uint64_t virtual_instr_address = vm_entry_disassembly[0].operands[0].imm.value.u;
	auto virtual_instr_content = binary->get_content_from_virtual_address(IMAGE + virtual_instr_address, 100000);

	std::vector<handler_t> handlers;
	int unique_handler_count = 1;
	int handler_count = 1;

	// extract handlers from vm
	for (int i = 0; i < virtual_instr_content.size();)
	{
		handler_t handler = {};

		if (i == 0)
		{
			handler.next_handler = *(uint32_t*)&virtual_instr_content[i];
			handler.instr_size = 4;
			handler.opcode = VM_INIT;
			handlers.push_back(handler);

			i += handler.instr_size;
			//std::cout << "handler " << std::dec << unique_handler_count << " at 0x" << std::hex << IMAGE + handler.next_handler << std::endl;
			unique_handler_count++;
			handler_count++;
			continue;
		}

		uint64_t handler_address = IMAGE + handlers[handlers.size() - 1].next_handler;
		auto handler_content = disassemble(binary->get_content_from_virtual_address(handler_address, 50), handler_address, ZYDIS_MNEMONIC_JMP);
		handler = utils::analyze_handler(handler_content);

		handler.address = virtual_instr_address + i;
		if (i + handler.instr_size >= virtual_instr_content.size() || handler.instr_size < 4)
			break;

		memcpy(&handler.data, &virtual_instr_content[i], handler.instr_size - 4);
		memcpy(&handler.next_handler, &virtual_instr_content[i + handler.instr_size - 4], 4);

		bool is_handler_unique = true;
		for (auto& tmp_handler : handlers)
		{
			if (handler.next_handler == tmp_handler.next_handler)
			{
				is_handler_unique = false;
				break;
			}
		}

		if (is_handler_unique)
		{
			//std::cout << "handler " << std::dec << unique_handler_count << " at 0x" << std::hex << IMAGE + handler.next_handler << std::endl;
			unique_handler_count++;
		}

		handler_count++;
		i += handler.instr_size;
		handlers.push_back(handler);
	}

	llvm::LLVMContext context;
	vm_lifter lifter(context, handlers);

	lifter.liftToLLVM();
	lifter.liftToVTIL();
}