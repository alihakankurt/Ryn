#ifndef __RYN_NATIVE_PLATFORM_HPP__
#define __RYN_NATIVE_PLATFORM_HPP__

#include <Ryn/Core.hpp>

namespace Ryn::Platform
{
    using Module = void*;

    Module LoadModule(const char* path);

    void FreeModule(Module handle);

    void* LoadFunction(Module handle, const char* name);

    template <typename TFunction>
    inline TFunction LoadFunction(Module handle, const char* name)
    {
        return As<TFunction>(LoadFunction(handle, name));
    }

    u64 GetTime();

    bool Write(const char* value, usize length);
}

#endif