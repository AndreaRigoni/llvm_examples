#include <iostream>
#include <string>
#include <vector>

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Module.h"
//#include "llvm/IR/DerivedTypes.h"
//#include "llvm/IR/IRBuilder.h"
//#include "llvm/IR/LegacyPassManager.h"
//#include "llvm/IR/Verifier.h"

#include "llvm/IRReader/IRReader.h"

#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"



using namespace llvm;
using namespace std;

int main(int argc, char **argv) {
    std::string filename = "hello_world.ll";
    if (argc > 1) {
        filename = argv[1];
    }

    // Parse the input LLVM IR file into a module.
    SMDiagnostic error;
    unique_ptr<Module> module = parseIRFile(filename, error, llvm::getGlobalContext());
    if (!module) {
        error.print(argv[0], llvm::errs());
        return 1;
    }


    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    std::string err_str;
    ExecutionEngine *engine = EngineBuilder(std::move(module))
            .setErrorStr(&err_str)
            // .setMCJITMemoryManager(new HelpingMemoryManager(this))
            .create();

    if (!engine) {
      exit(1);
    }

    engine->finalizeObject();

    // solution 1)
    // vector<GenericValue> args;
    // engine->runFunction(module->getFunction("main"),args);

    // solution 2)
    int(*_main)(void) = (int(*)(void))engine->getPointerToNamedFunction("main");
    if(_main) _main();

}





