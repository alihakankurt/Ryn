#if RYN_PLATFORM_MACOS || RYN_PLATFORM_LINUX

#include <Ryn/Native/Platform.hpp>

#include <unistd.h>
#include <dlfcn.h>
#include <sys/time.h>

namespace Ryn::Platform
{
    Module LoadModule(cstring path)
    {
        return dlopen(path, RTLD_LAZY);
    }

    void FreeModule(Module handle)
    {
        dlclose(handle);
    }

    void* LoadFunction(void* handle, cstring name)
    {
        return dlsym(handle, name);
    }

    u64 GetTime()
    {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        return As<u64>(tv.tv_sec * 1'000'000 + tv.tv_usec);
    }

    bool Write(cstring value, usize length)
    {
        isize result = write(STDOUT_FILENO, value, length);
        return result >= 0 && As<usize>(result) == length;
    }
}

#endif