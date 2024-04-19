#ifndef __RYN_NATIVE_OPENGL_HPP__
#define __RYN_NATIVE_OPENGL_HPP__

#include <Ryn/Core.hpp>

namespace Ryn::OpenGL
{
    enum struct ClearMask : u32
    {
        Color = 0x00004000,
        Depth = 0x00000100,
        Stencil = 0x00000400
    };

    using ClearFunction = void (*)(ClearMask mask);
    extern ClearFunction Clear;

    using ClearColorFunction = void (*)(f32 red, f32 green, f32 blue, f32 alpha);
    extern ClearColorFunction ClearColor;

    bool Load();
    void Unload();
}

#endif