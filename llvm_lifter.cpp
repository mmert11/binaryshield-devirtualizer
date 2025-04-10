#include "vm.hpp"

vm_lifter::vm_lifter(LLVMContext& ctx, std::vector<handler_t> handlers_)
	: context(ctx), builder(ctx), module(new Module("devirt_module", ctx)), handlers(handlers_)
{
	Type* int64_t = Type::getInt64Ty(context);
	Type* void_t = Type::getVoidTy(context);
	Type* ptr_t = PointerType::get(int64_t, 0);

	FunctionType* FuncType = FunctionType::get(void_t, {  }, false);
	function = Function::Create(FuncType, Function::ExternalLinkage, "devirtualized", module);

	//rsp = &*function->arg_begin();
	//rsp->setName("rsp");

	BasicBlock* EntryBB = BasicBlock::Create(context, "entry", function);
	builder.SetInsertPoint(EntryBB);

	ArrayType* stackType = ArrayType::get(builder.getInt8Ty(), 2048);
	AllocaInst* StackArray = builder.CreateAlloca(stackType, nullptr, "vstack_memory");

	vsp = builder.CreateGEP(
		stackType, StackArray,
		{ ConstantInt::get(builder.getInt32Ty(), 0),
		  ConstantInt::get(builder.getInt32Ty(), 2048) },
		"vsp"
	);

	vtil_ = new vtil_lifter(handlers);
}

void vm_lifter::liftToLLVM()
{
	for (int i = 0; i < handlers.size(); i++)
	{
		handler_t& handler = handlers[i];
		BasicBlock* handler_block = BasicBlock::Create(context, std::string(handler.parseToStr() + "_" + std::to_string(i)), function);
		handler.block = handler_block;
	}

	builder.CreateBr(handlers[0].block);

	for (int i = 0; i < handlers.size(); i++)
	{
		handler_t& handler = handlers[i];
		builder.SetInsertPoint(handler.block);

		if (i == handlers.size() - 1)
			break;

		BasicBlock* next_block = handlers[i + 1].block;
		switch (handler.opcode)
		{
		case VM_INIT:
			//vm_init();
			break;
		case POP_VR64:
			pop_vr64(handler);
			break;
		case POP_VR32:
			pop_vr32(handler);
			break;
		case PUSH_VR64:
			push_vr64(handler);
			break;
		case PUSH_VR32:
			push_vr32(handler);
			break;
		case PUSH_VSP:
			push_vsp();
			break;
		case POP_VSP:
			pop_vsp();
			break;
		case PUSH_64:
			push_64(handler);
			break;
		case PUSH_32:
			push_32(handler);
			break;
		case SUB64:
			sub_64(handler);
			break;
		case SUB32:
			sub_32(handler);
			break;
		case ADD64:
			add_64(handler);
			break;
		case ADD32:
			add_32();
			break;
		case WRITE32:
			write_32();
			break;
		case LOAD32:
			load_32();
			break;
		case LOAD64:
			load_64();
			break;
		case OR_32:
			or_32();
			break;
		case AND_32:
			and_32();
			break;
		case XOR_32:
			xor_32();
			break;
		case JNZ:
		{
			BasicBlock* target_block = nullptr;
			for (int j = 0; j < handlers.size(); j++)
			{
				if (handlers[j].address == handler.data)
				{
					target_block = handlers[j].block;
					break;
				}
			}
			llvm::Value* condition = jnz();
			builder.CreateCondBr(condition, target_block, next_block);
			continue;
		}
		}

		builder.CreateBr(next_block);
	}

	//vm_exit();
	builder.CreateRetVoid();
	optimizeLLVM(llvm::OptimizationLevel::O3);

	verifyFunction(*function);

	module->print(outs(), nullptr);

	std::error_code EC;
	llvm::raw_fd_ostream dest("output.ll", EC, llvm::sys::fs::OF_None);

	if (EC) {
		errs() << "Error opening file: " << EC.message() << "\n";
	}
	else {
		module->print(dest, nullptr);
	}

	module->~Module();
}

void vm_lifter::optimizeLLVM(llvm::OptimizationLevel level)
{
	if (!this->module) {
		llvm::errs() << "Error: Module is null!\n";
		return;
	}

	llvm::PassBuilder PB;

	llvm::LoopAnalysisManager LAM;
	llvm::FunctionAnalysisManager FAM;
	llvm::CGSCCAnalysisManager CGAM;
	llvm::ModuleAnalysisManager MAM;

	PB.registerModuleAnalyses(MAM);
	PB.registerCGSCCAnalyses(CGAM);
	PB.registerFunctionAnalyses(FAM);
	PB.registerLoopAnalyses(LAM);
	PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

	llvm::ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(level);

	MPM.run(*this->module, MAM);
}

void vm_lifter::vm_init()
{
	//vsp = rsp; return;
	for (int i = 0; i <= 15; i++)
	{
		vpush64(rpop64());
	}
}

void vm_lifter::vm_exit()
{
	for (int i = 0; i <= 15; i++)
	{
		rpush64(vpop64());
	}
}

void vm_lifter::pop_vr64(handler_t handler)
{
	//builder.CreateStore(vpop64(), builder.CreatePointerCast(vregs[handler.data], builder.getInt64Ty()->getPointerTo()));
	vregs[handler.data] = vpop64();
}

void vm_lifter::pop_vr32(handler_t handler)
{
	//builder.CreateStore(vpop32(), builder.CreatePointerCast(vregs[handler.data], builder.getInt32Ty()->getPointerTo()));
	vregs[handler.data] = vpop32();
}

void vm_lifter::push_vr64(handler_t handler)
{
	//vpush64(builder.CreateLoad(builder.getInt64Ty(), builder.CreatePointerCast(vregs[handler.data], builder.getInt64Ty()->getPointerTo())));
	vpush64(vregs[handler.data]);
}

void vm_lifter::push_vr32(handler_t handler)
{
	//vpush32(builder.CreateLoad(builder.getInt32Ty(), builder.CreatePointerCast(vregs[handler.data], builder.getInt32Ty()->getPointerTo())));
	vpush32(vregs[handler.data]);
}

void vm_lifter::push_vsp()
{
	vpush64(builder.CreatePtrToInt(vsp, builder.getInt64Ty()));
}

void vm_lifter::pop_vsp()
{
	vsp = builder.CreateIntToPtr(vpop64(), builder.getInt8Ty()->getPointerTo());
}

void vm_lifter::push_64(handler_t handler)
{
	vpush64(ConstantInt::get(builder.getInt64Ty(), handler.data));
}

void vm_lifter::push_32(handler_t handler)
{
	vpush32(ConstantInt::get(builder.getInt32Ty(), *(uint32_t*)&handler.data));
}

llvm::Value* vm_lifter::calc_zero_flag(llvm::Value* result)
{
	llvm::Value* cmp = builder.CreateICmpEQ(builder.CreateSExt(result, builder.getInt64Ty()), builder.getInt64(0), "zf");
	return builder.CreateSExt(cmp, builder.getInt64Ty(), "zf_ext");
}

void vm_lifter::sub_64(handler_t handler)
{
	llvm::Value* first = vpop64();
	llvm::Value* second = vpop64();
	llvm::Value* result = builder.CreateSub(second, first, "sub_64_result");

	vpush64(result);
	vpush64(calc_zero_flag(result));
}

void vm_lifter::sub_32(handler_t handler)
{
	llvm::Value* first = vpop32();
	llvm::Value* second = vpop32();
	llvm::Value* result = builder.CreateSub(second, first, "sub_32_result");

	vpush32(result);
	vpush64(calc_zero_flag(result));
}

void vm_lifter::add_64(handler_t handler)
{
	llvm::Value* first = vpop64();
	llvm::Value* second = vpop64();
	llvm::Value* result = builder.CreateAdd(second, first, "add_64_result");

	vpush64(result);
	vpush64(calc_zero_flag(result));
}

void vm_lifter::add_32()
{
	llvm::Value* first = vpop32();
	llvm::Value* second = vpop32();
	llvm::Value* result = builder.CreateAdd(second, first, "add_32_result");

	vpush32(result);
	vpush64(calc_zero_flag(result));
}

void vm_lifter::write_32()
{
	llvm::Value* address = vpop64();
	llvm::Value* value = vpop32();
	llvm::Value* pointer = builder.CreateIntToPtr(address, builder.getInt32Ty()->getPointerTo());
	builder.CreateStore(value, pointer);
}

void vm_lifter::load_32()
{
	llvm::Value* address = vpop64();
	llvm::Value* pointer = builder.CreateIntToPtr(address, builder.getInt32Ty()->getPointerTo());
	llvm::Value* value = builder.CreateLoad(builder.getInt32Ty(), pointer);
	vpush32(value);
}

void vm_lifter::load_64()
{
	llvm::Value* address = vpop64();
	llvm::Value* pointer = builder.CreateIntToPtr(address, builder.getInt64Ty()->getPointerTo());
	llvm::Value* value = builder.CreateLoad(builder.getInt64Ty(), pointer);
	vpush64(value);
}

void vm_lifter::or_32()
{
	llvm::Value* first = vpop32();
	llvm::Value* second = vpop32();
	llvm::Value* result = builder.CreateOr(second, first, "or_32_result");

	vpush32(result);
	vpush64(calc_zero_flag(result));
}

void vm_lifter::and_32()
{
	llvm::Value* first = vpop32();
	llvm::Value* second = vpop32();
	llvm::Value* result = builder.CreateAnd(second, first, "and_32_result");

	vpush32(result);
	vpush64(calc_zero_flag(result));
}

void vm_lifter::xor_32()
{
	llvm::Value* first = vpop32();
	llvm::Value* second = vpop32();
	llvm::Value* result = builder.CreateXor(second, first, "xor_32_result");

	vpush32(result);
	vpush64(calc_zero_flag(result));
}

llvm::Value* vm_lifter::jnz()
{
	llvm::Value* zf = vpop64();
	llvm::Value* condition = builder.CreateICmpNE(zf, builder.getInt64(0), "zf_cond");
	return condition;
}
