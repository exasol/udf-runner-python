#pragma once

#include <functional>
#include <string>

#include "exaudflib/vm/swig_vm.h"

std::function<SWIGVMContainers::SWIGVM*()> create_vm(const std::string& argv_lang);
