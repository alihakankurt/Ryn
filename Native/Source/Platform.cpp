#include <Ryn/Native/Platform.hpp>

#if RYN_PLATFORM_WINDOWS

#error "Windows platform is not supported yet."

#elif RYN_PLATFORM_MACOS || RYN_PLATFORM_LINUX

#include <dlfcn.h>
#include <sys/time.h>

namespace Ryn::Platform
{
    Module LoadModule(const char* path)
    {
        return dlopen(path, RTLD_LAZY);
    }

    void FreeModule(Module handle)
    {
        dlclose(handle);
    }

    void* LoadFunction(void* handle, const char* name)
    {
        return dlsym(handle, name);
    }

    u64 GetTime()
    {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        return As<u64>(tv.tv_sec * 1'000'000 + tv.tv_usec);
    }
}

#endif