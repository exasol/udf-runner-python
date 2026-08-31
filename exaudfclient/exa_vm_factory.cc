#include <functional>
#include <cstdlib>
#include <iostream>

#include "exa_vm_factory.h"

#ifdef ENABLE_PYTHON_VM
#include "base/python/pythoncontainer.h"
#endif

std::function<SWIGVMContainers::SWIGVM*()> create_vm(const std::string& argv_lang) {
    if (argv_lang != "lang=python") {
        throw SWIGVMContainers::SWIGVM::exception("unsupported language specified in argv");
    }
#ifdef ENABLE_PYTHON_VM
    char *path_var = getenv("PATH");
    if (path_var != nullptr) {
        std::string path_var_str = std::string(path_var);
        path_var_str.insert(0, "/opt/conda/bin:");
        if (setenv("PATH", path_var_str.c_str(), 1) == -1) {
            std::cerr << "Unable to prefix PATH env variable with /opt/conda/bin";
        }
    }
    return []() { return new SWIGVMContainers::PythonVM(false); };
#else
    throw SWIGVMContainers::SWIGVM::exception("this exaudfclient has been compiled without Python support");
#endif
}
