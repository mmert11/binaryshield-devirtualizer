#include "vm.hpp"
#pragma optimize("", off)

vtil_lifter::vtil_lifter(std::vector<handler_t> handlers_) :
	handlers(handlers_)
{
	for (int i = 0; i < 17; i++) {
		vregs.emplace_back(register_desc(register_virtual, i, 64));
	}
}

#pragma optimize("", off)

void vtil_lifter::lift()
{
	block = rtn->create_block(handlers[0].address).first;
	handlers[0].vblock = block;

	for (int i = 0; i < handlers.size(); i++)
	{
		handler_t instruction = handlers[i];
		auto handler = [&](auto recurse, handler_t instruction) -> void
			{
				if (instruction.vblock == nullptr)
				{
					crashed("block is not created for " << instruction.parseToStr() << ":" << i);
				}
				block = instruction.vblock;

				switch (instruction.opcode)
				{
				case VM_INIT:
				{
					block->push(0x1678F);
					block->push(pregs[X86_REG_R15]);
					block->push(pregs[X86_REG_R14]);
					block->push(pregs[X86_REG_R13]);
					block->push(pregs[X86_REG_R12]);
					block->push(pregs[X86_REG_R11]);
					block->push(pregs[X86_REG_R10]);
					block->push(pregs[X86_REG_R9]);
					block->push(pregs[X86_REG_R8]);
					block->push(pregs[X86_REG_RBP]);
					block->push(pregs[X86_REG_RDI]);
					block->push(pregs[X86_REG_RSI]);
					block->push(pregs[X86_REG_RDX]);
					block->push(pregs[X86_REG_RCX]);
					block->push(pregs[X86_REG_RBX]);
					block->push(pregs[X86_REG_RAX]);
					block->pushf();
					break;
				}
				case POP_VR64:
				{
					block->pop(vregs[instruction.data]);
					break;
				}
				case POP_VR32:
				{
					auto tmp_reg = block->tmp(32);
					block->vpinr(tmp_reg);
					block->pop(tmp_reg);
					block->mov(vregs[instruction.data], tmp_reg);
					break;
				}
				case PUSH_VR64:
				{
					block->push(vregs[instruction.data]);
					break;
				}
				case PUSH_VR32:
				{
					auto tmp_reg = block->tmp(32);
					block->vpinw(tmp_reg);
					block->mov(tmp_reg, vregs[instruction.data]);
					block->push(tmp_reg);
					break;
				}
				case PUSH_VSP:
				{
					auto tmp_reg = block->tmp(64);
					block->push(vtil::REG_SP);
					break;
				}
				case POP_VSP:
				{
					block->pop(vtil::REG_SP);
					break;
				}
				case PUSH_64:
				{
					block->push(instruction.data);
					break;
				}
				case PUSH_32:
				{
					auto tmp_reg = block->tmp(32);
					block->vpinw(tmp_reg);
					block->mov(tmp_reg, *(uint32_t*)&instruction.data);
					block->push(tmp_reg);
					break;
				}
				case SUB64:
				{
					auto tmp_reg1 = block->tmp(64);
					auto tmp_reg2 = block->tmp(64);
					auto zero_reg = block->tmp(64);
					block->mov(zero_reg, 0);

					block->pop(tmp_reg1);
					block->pop(tmp_reg2);
					block->sub(tmp_reg2, tmp_reg1);
					block->te(REG_FLAGS, tmp_reg2, zero_reg);

					block->push(tmp_reg2);
					block->push(vtil::REG_FLAGS);
					break;
				}
				case SUB32:
				{
					auto tmp_reg1 = block->tmp(32);
					auto tmp_reg2 = block->tmp(32);
					auto zero_reg = block->tmp(64);
					block->mov(zero_reg, 0);

					block->pop(tmp_reg1);
					block->pop(tmp_reg2);
					block->sub(tmp_reg2, tmp_reg1);
					block->te(REG_FLAGS, tmp_reg2, zero_reg);

					block->push(tmp_reg2);
					block->push(vtil::REG_FLAGS);
					break;
				}
				case ADD64:
				{
					auto tmp_reg1 = block->tmp(64);
					auto tmp_reg2 = block->tmp(64);
					auto zero_reg = block->tmp(64);
					block->mov(zero_reg, 0);

					block->pop(tmp_reg1);
					block->pop(tmp_reg2);
					block->add(tmp_reg2, tmp_reg1);
					block->te(REG_FLAGS, tmp_reg2, zero_reg);

					block->push(tmp_reg2);
					block->push(vtil::REG_FLAGS);
					break;
				}
				case ADD32:
				{
					auto tmp_reg1 = block->tmp(32);
					auto tmp_reg2 = block->tmp(32);
					auto zero_reg = block->tmp(64);
					block->mov(zero_reg, 0);

					block->pop(tmp_reg1);
					block->pop(tmp_reg2);
					block->add(tmp_reg2, tmp_reg1);
					block->te(REG_FLAGS, tmp_reg2, zero_reg);

					block->push(tmp_reg2);
					block->push(vtil::REG_FLAGS);
					break;
				}
				case WRITE32:
				{
					auto tmp_reg1 = block->tmp(64);
					auto tmp_reg2 = block->tmp(32);
					block->str(tmp_reg1, 0, tmp_reg2);
					break;
				}
				case LOAD32:
				{
					auto tmp_reg1 = block->tmp(64);
					auto tmp_reg2 = block->tmp(32);
					block->ldd(tmp_reg2, tmp_reg1, 0);
					block->push(tmp_reg2);
					break;
				}
				case LOAD64:
				{
					auto tmp_reg1 = block->tmp(64);
					auto tmp_reg2 = block->tmp(64);
					block->ldd(tmp_reg2, tmp_reg1, 0);
					block->push(tmp_reg2);
					break;
				}
				case OR_32:
				{
					auto tmp_reg1 = block->tmp(32);
					auto tmp_reg2 = block->tmp(32);
					auto zero_reg = block->tmp(64);
					block->mov(zero_reg, 0);

					block->pop(tmp_reg1);
					block->pop(tmp_reg2);
					block->bor(tmp_reg2, tmp_reg1);
					block->te(REG_FLAGS, tmp_reg2, zero_reg);

					block->push(tmp_reg2);
					block->push(vtil::REG_FLAGS);
					break;
				}
				case AND_32:
				{
					auto tmp_reg1 = block->tmp(32);
					auto tmp_reg2 = block->tmp(32);
					auto zero_reg = block->tmp(64);
					block->mov(zero_reg, 0);

					block->pop(tmp_reg1);
					block->pop(tmp_reg2);
					block->band(tmp_reg2, tmp_reg1);
					block->te(REG_FLAGS, tmp_reg2, zero_reg);

					block->push(tmp_reg2);
					block->push(vtil::REG_FLAGS);
					break;
				}
				case XOR_32:
				{
					auto tmp_reg1 = block->tmp(32);
					auto tmp_reg2 = block->tmp(32);
					auto zero_reg = block->tmp(64);
					block->mov(zero_reg, 0);

					block->pop(tmp_reg1);
					block->pop(tmp_reg2);
					block->bxor(tmp_reg2, tmp_reg1);
					block->te(REG_FLAGS, tmp_reg2, zero_reg);

					block->push(tmp_reg2);
					block->push(vtil::REG_FLAGS);
					break;
				}
				case JNZ:
				{
					auto zf = block->tmp(64);
					block->pop(zf);

					basic_block* target_block = nullptr;
					for (int j = 0; j < handlers.size(); j++)
					{
						if (handlers[j].address == instruction.data)
						{
							block->tne(REG_FLAGS, zf, 0);
							block->js(REG_FLAGS, handlers[j].address, handlers[i+1].address);

							if (handlers[j].vblock == nullptr && !rtn->explored_blocks.contains(handlers[j].address))
								handlers[j].vblock = block->fork(handlers[j].address);
							else
								block->fork(handlers[j].address);

							if (handlers[i + 1].vblock == nullptr)
								handlers[i + 1].vblock = block->fork(handlers[i + 1].address);

							target_block = handlers[j].vblock;
							break;
						}
					}
					if (target_block == nullptr)
					{
						crashed("couldnt resolve jnz address");
					}

					return;
				}
				default:
					crashed("encountered an unknown opcode");
					break;
				}

				if (i < handlers.size() - 1)
				{
					block->jmp(handlers[i + 1].address);
					if (!rtn->explored_blocks.contains(handlers[i+1].address))
						handlers[i + 1].vblock = block->fork(handlers[i + 1].address);
				}
				else
				{
					block->popf();
					block->pop(pregs[X86_REG_R15]);
					block->pop(pregs[X86_REG_R14]);
					block->pop(pregs[X86_REG_R13]);
					block->pop(pregs[X86_REG_R12]);
					block->pop(pregs[X86_REG_R11]);
					block->pop(pregs[X86_REG_R10]);
					block->pop(pregs[X86_REG_R9]);
					block->pop(pregs[X86_REG_R8]);
					block->pop(pregs[X86_REG_RBP]);
					block->pop(pregs[X86_REG_RDI]);
					block->pop(pregs[X86_REG_RSI]);
					block->pop(pregs[X86_REG_RDX]);
					block->pop(pregs[X86_REG_RCX]);
					block->pop(pregs[X86_REG_RBX]);
					block->pop(pregs[X86_REG_RAX]);
					block->vexit(pregs[X86_REG_RAX]);
				}
			};
		handler(handler, instruction);
	}
}

void vm_lifter::liftToVTIL()
{
	vtil_->lift();
	//vtil::optimizer::apply_all(vtil_->rtn);
	//vtil::debug::dump(vtil_->rtn);
	vtil::save_routine(vtil_->rtn, "output.vtil");
}

void vtil_lifter::vm_entry()
{

}

