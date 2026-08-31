#include <cstring>
#include <iostream>

#include "exa_udf_client.h"
#include "exa_vm_factory.h"

void ExaUdfClient::parse_arguments(int argc, char** argv) {
    m_languageArg = argv[2];
}

bool ExaUdfClient::validate_arguments(int argc, char** argv) {
    if (argc != 3 || strcmp(argv[2], "lang=python") != 0) {
        usage(argv[0]);
        return false;
    }
    return true;
}

void ExaUdfClient::usage(const std::string& programName) {
    std::cerr << "Usage: " << programName << " <socket> lang=python" << std::endl;
}

std::function<SWIGVMContainers::SWIGVM*()> ExaUdfClient::create_vm() {
    return ::create_vm(m_languageArg);
}
