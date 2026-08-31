#include <functional>

#include "exa_vm_factory.h"

#ifdef ENABLE_PYTHON_VM
#include "base/python/pythoncontainer.h"
#endif

std::function<SWIGVMContainers::SWIGVM*()> create_vm(const std::string& argv_lang) {
    if (argv_lang != "lang=python") {
        throw SWIGVMContainers::SWIGVM::exception("unsupported language specified in argv");
    }
#ifdef ENABLE_PYTHON_VM
    return []() { return new SWIGVMContainers::PythonVM(false); };
#else
    throw SWIGVMContainers::SWIGVM::exception("this exaudfclient has been compiled without Python support");
#endif
}
