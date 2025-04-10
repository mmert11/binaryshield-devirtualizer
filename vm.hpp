#pragma once
#pragma optimize("", on)
#pragma warning( disable : 4146 )
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define crashed(message) std::cerr << "error: " << message << " | " << __FILENAME__ << ":" << __LINE__ << "\n"; exit(-1)

#include <stdint.h>
#include <vector>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Passes/Passbuilder.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils.h>
#include <llvm/Transforms/Scalar/SimplifyCFG.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"
#include <llvm/IR/Constants.h>

#include "binary.hpp"

#include <vtil/vtil>

using namespace llvm;

enum v_opcode_t
{
	UNKNOWN,
	VM_INIT,
	VM_EXIT,
	POP_VR64,
	POP_VR32,
	PUSH_VR64,
	PUSH_VR32,
	PUSH_VSP,
	POP_VSP,
	PUSH_64,
	PUSH_32,
	SUB64,
	SUB32,
	ADD64,
	ADD32,
	WRITE32,
	LOAD32,
	LOAD64,
	OR_32,
	AND_32,
	XOR_32,
	JNZ
};

class handler_t
{
public:
	v_opcode_t opcode = UNKNOWN;
	uint64_t data;
	uint32_t address;
	uint32_t next_handler;
	int instr_size;
	llvm::BasicBlock* block;
	vtil::basic_block* vblock = nullptr;

	std::string parseToStr()
	{
		static const std::unordered_map<v_opcode_t, std::string> opcode_map =
		{
			{UNKNOWN, "UNKNOWN"},
			{VM_INIT, "VM_INIT"},
			{VM_EXIT, "VM_EXIT"},
			{POP_VR64, "POP_VR64"},
			{PUSH_VR64, "PUSH_VR64"},
			{PUSH_VSP, "PUSH_vsp"},
			{POP_VSP, "POP_vsp"},
			{PUSH_64, "PUSH_64"},
			{SUB64, "SUB64"},
			{ADD64, "ADD64"},
			{PUSH_VR32, "PUSH_VR32"},
			{WRITE32, "WRITE32"},
			{PUSH_32, "PUSH_32"},
			{LOAD32, "LOAD32"},
			{LOAD64, "LOAD64"},
			{OR_32, "OR_32"},
			{AND_32, "AND_32"},
			{ADD32, "ADD32"},
			{SUB32, "SUB32"},
			{XOR_32, "XOR_32"},
			{POP_VR32, "POP_VR32"},
			{JNZ, "JNZ"}
		};

		auto it = opcode_map.find(opcode);
		return it != opcode_map.end() ? it->second : "UNHANDLED_OPCODE";
	}
};

using namespace vtil;
class vtil_lifter
{
public:
	vtil_lifter(std::vector<handler_t> handlers_);
	routine* rtn = new routine(vtil::architecture_amd64);
	std::vector<handler_t> handlers;
	void lift();
private:
	vip_t vip = 0;
	basic_block* block = nullptr;

	void vm_entry();

	std::vector<register_desc> vregs;
	std::unordered_map<int, register_desc> pregs = {
	{ X86_REG_RAX, register_desc(register_physical, X86_REG_RAX, 64, 0) },
	{ X86_REG_RBX, register_desc(register_physical, X86_REG_RBX, 64, 0) },
	{ X86_REG_RCX, register_desc(register_physical, X86_REG_RCX, 64, 0) },
	{ X86_REG_RDX, register_desc(register_physical, X86_REG_RDX, 64, 0) },
	{ X86_REG_RSI, register_desc(register_physical, X86_REG_RSI, 64, 0) },
	{ X86_REG_RDI, register_desc(register_physical, X86_REG_RDI, 64, 0) },
	{ X86_REG_RBP, register_desc(register_physical, X86_REG_RBP, 64, 0) },
	{ X86_REG_RSP, register_desc(register_physical, X86_REG_RSP, 64, 0) },
	{ X86_REG_R8,  register_desc(register_physical, X86_REG_R8, 64, 0) },
	{ X86_REG_R9,  register_desc(register_physical, X86_REG_R9, 64, 0) },
	{ X86_REG_R10, register_desc(register_physical, X86_REG_R10, 64, 0) },
	{ X86_REG_R11, register_desc(register_physical, X86_REG_R11, 64, 0) },
	{ X86_REG_R12, register_desc(register_physical, X86_REG_R12, 64, 0) },
	{ X86_REG_R13, register_desc(register_physical, X86_REG_R13, 64, 0) },
	{ X86_REG_R14, register_desc(register_physical, X86_REG_R14, 64, 0) },
	{ X86_REG_R15, register_desc(register_physical, X86_REG_R15, 64, 0) }
	};
};

class vm_lifter {
public:

	LLVMContext& context;
	IRBuilder<> builder;
	Module* module;
	Function* function;

	std::vector<handler_t> handlers;

	std::vector<llvm::Value*> vregs = std::vector<llvm::Value*>(32);
	llvm::Value* rsp;
	llvm::Value* vsp;

	vm_lifter(LLVMContext& ctx, std::vector<handler_t> handlers_);
	void liftToLLVM();
	void optimizeLLVM(llvm::OptimizationLevel level);

	void liftToVTIL();

private:
	vtil_lifter* vtil_;
	llvm::Value* calc_zero_flag(llvm::Value* result);

	void vm_init();
	void vm_exit();
	void pop_vr64(handler_t handler);
	void pop_vr32(handler_t handler);
	void push_vr64(handler_t handler);
	void push_vr32(handler_t handler);
	void push_vsp();
	void pop_vsp();
	void push_64(handler_t handler);
	void push_32(handler_t handler);
	void sub_64(handler_t handler);
	void sub_32(handler_t handler);
	void add_64(handler_t handler);
	void add_32();
	void write_32();
	void load_32();
	void load_64();
	void or_32();
	void and_32();
	void xor_32();
	llvm::Value* jnz();

	void vpush64(Value* val) {
		vsp = builder.CreateGEP(builder.getInt8Ty(), vsp,
			ConstantInt::get(builder.getInt64Ty(), -8), "vsp_dec64");
		Value* ptr64 = builder.CreatePointerCast(vsp, builder.getInt64Ty()->getPointerTo(), "ptr64");
		builder.CreateStore(val, ptr64);
	}

	Value* vpop64() {
		Value* ptr64 = builder.CreatePointerCast(vsp, builder.getInt64Ty()->getPointerTo(), "ptr64");
		Value* ret = builder.CreateLoad(builder.getInt64Ty(), ptr64);
		vsp = builder.CreateGEP(builder.getInt8Ty(), vsp,
			ConstantInt::get(builder.getInt64Ty(), 8), "vsp_inc64");
		return ret;
	}

	void vpush32(Value* val) {
		vsp = builder.CreateGEP(builder.getInt8Ty(), vsp,
			ConstantInt::get(builder.getInt64Ty(), -4), "vsp_dec32");
		Value* truncVal = builder.CreateTrunc(val, builder.getInt32Ty(), "trunc32");
		Value* ptr32 = builder.CreatePointerCast(vsp, builder.getInt32Ty()->getPointerTo(), "ptr32");
		builder.CreateStore(truncVal, ptr32);
	}

	Value* vpop32() {
		Value* ptr32 = builder.CreatePointerCast(vsp, builder.getInt32Ty()->getPointerTo(), "ptr32");
		Value* ret = builder.CreateLoad(builder.getInt32Ty(), ptr32);
		vsp = builder.CreateGEP(builder.getInt8Ty(), vsp,
			ConstantInt::get(builder.getInt64Ty(), 4), "vsp_inc32");
		return ret;
	}

	void rpush64(llvm::Value* value) {
		rsp = builder.CreateGEP(builder.getInt8Ty(), rsp, ConstantInt::get(builder.getInt64Ty(), -8));
		Value* ptr64 = builder.CreatePointerCast(rsp, builder.getInt64Ty()->getPointerTo());
		builder.CreateStore(value, ptr64);
	}

	llvm::Value* rpop64() {
		Value* ptr64 = builder.CreatePointerCast(rsp, builder.getInt64Ty()->getPointerTo());
		Value* value = builder.CreateLoad(builder.getInt64Ty(), ptr64);

		rsp = builder.CreateGEP(builder.getInt8Ty(), rsp, ConstantInt::get(builder.getInt64Ty(), 8));
		return value;
	}
};

namespace utils
{
	handler_t analyze_handler(std::vector<native_instruction_t> handler_content)
	{
		handler_t handler = {};
		for (int i = 0; i < handler_content.size(); i++)
		{
			native_instruction_t native_instruction = handler_content[i];

			if (native_instruction.i.mnemonic == ZYDIS_MNEMONIC_ADD && native_instruction.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
				native_instruction.operands[0].reg.value == ZYDIS_REGISTER_R13 && native_instruction.operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE)
			{
				handler.instr_size += native_instruction.operands[1].imm.value.s;
			}
			else if (native_instruction.i.mnemonic == ZYDIS_MNEMONIC_INC && native_instruction.operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
				native_instruction.operands[0].reg.value == ZYDIS_REGISTER_R13)
			{
				handler.instr_size++;
			}
			else if (native_instruction.i.mnemonic == ZYDIS_MNEMONIC_JMP)
			{
				break;
			}
		}

		static const std::unordered_map<uint64_t, v_opcode_t> opcode_map = {
			   {0x140016101, POP_VR64},
			   {0x14001606a, PUSH_VR64},
			   {0x14001620a, PUSH_VSP},
			   {0x140016194, PUSH_64},
			   {0x14001631f, SUB64},
			   {0x14001626c, POP_VSP},
			   {0x1400162B1, ADD64},
			   {0x140016090, PUSH_VR32},
			   {0x140016707, WRITE32},
			   {0x1400161b1, PUSH_32},
			   {0x14001669F, LOAD32},
			   {0x140016689, LOAD64},
			   {0x140016481, OR_32},
			   {0x140016413, AND_32},
			   {0x1400162C9, ADD32},
			   {0x140016337, SUB32},
			   {0x1400163a5, XOR_32},
			   {0x140016126, POP_VR32},
			   {0x14001676b, JNZ}
		};

		auto it = opcode_map.find(handler_content[0].address);
		if (it != opcode_map.end()) 
			handler.opcode = it->second;

		return handler;
	}
}