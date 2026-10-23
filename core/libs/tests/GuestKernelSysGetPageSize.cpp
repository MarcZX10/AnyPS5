#include "prx/libc/include/general/VabiMacros.hpp"
#include <cstdio>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace {

using GetPageSize = int(APS5_VABI*)();

void Require(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "%s\n", message);
        std::abort();
    }
}

}

int main(int argc, char** argv) {
    Require(argc == 3, "expected the libkernel and libkernel_sys paths");
#ifdef _WIN32
    const auto kernel = LoadLibraryA(argv[1]);
    Require(kernel != nullptr, "could not load libkernel");
    const auto module = LoadLibraryA(argv[2]);
    Require(module != nullptr, "could not load libkernel_sys");
    const auto getPageSize = reinterpret_cast<GetPageSize>(GetProcAddress(module, "getpagesize_nid_postfix"));
#else
    const auto kernel = dlopen(argv[1], RTLD_NOW | RTLD_GLOBAL);
    Require(kernel != nullptr, "could not load libkernel");
    const auto module = dlopen(argv[2], RTLD_NOW | RTLD_LOCAL);
    Require(module != nullptr, "could not load libkernel_sys");
    const auto getPageSize = reinterpret_cast<GetPageSize>(dlsym(module, "getpagesize_nid_postfix"));
#endif
    Require(getPageSize != nullptr, "getpagesize is missing from libkernel_sys");
    Require(getPageSize() == 0x4000, "getpagesize returned a value other than the PS5 page size");
    return 0;
}
