#include <iostream>
#include <cstring>

#include "exa_udf_client.h"
#include "exa_vm_factory.h"

void ExaUdfClient::parse_arguments(int argc, char** argv) {
    //  Now assumption is that all cmd line aguments are already validated.
    m_languageArg = argv[2];
   
}

bool ExaUdfClient::validate_arguments(int argc, char** argv) {
    if (argc != 3) {
        usage(argv[0]);
        return false;
    }

    if (!((strcmp(argv[2], "lang=python") == 0)
        || (strcmp(argv[2], "lang=streaming") == 0)
        || (strcmp(argv[2], "lang=benchmark") == 0))) {
        usage(argv[0]);
        return false;
    }

    return true;
}

void ExaUdfClient::usage(const std::string& programName) {
    std::cerr << "Usage: " << programName
              << " <socket> lang=python|lang=streaming|lang=benchmark"
              << std::endl;
}

std::function<SWIGVMContainers::SWIGVM*()> ExaUdfClient::create_vm() {
    return ::create_vm(m_languageArg);
}
