#ifndef __RYN_NATIVE_OPENGL_HPP__
#define __RYN_NATIVE_OPENGL_HPP__

#include <Ryn/Core.hpp>

namespace Ryn::OpenGL
{
    using ClearFunction = void (*)(u32 mask);
    extern ClearFunction Clear;

    using ClearColorFunction = void (*)(f32 red, f32 green, f32 blue, f32 alpha);
    extern ClearColorFunction ClearColor;

    bool Load();
    void Unload();
}

#endif