#ifndef __RYN_NATIVE_PLATFORM_HPP__
#define __RYN_NATIVE_PLATFORM_HPP__

#include <Ryn/Core.hpp>

namespace Ryn::Platform
{
    using Module = void*;

    Module LoadModule(cstring path);

    void FreeModule(Module handle);

    void* LoadFunction(Module handle, cstring name);

    template <typename TFunction>
    inline TFunction LoadFunction(Module handle, cstring name)
    {
        return As<TFunction>(LoadFunction(handle, name));
    }

    u64 GetTime();

    bool Write(cstring value, usize length);

    usize ReadFile(cstring path, char*& buffer);
}

#endif