#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    enum class MouseButton
    {
        Unknown,

        Button1,
        Button2,
        Button3,
        Button4,
        Button5,
        Button6,
        Button7,
        Button8,

        Count,

        Left = Button1,
        Right = Button2,
        Middle = Button3,
    };

    constexpr u32 operator+(MouseButton button) { return static_cast<u32>(button); }
}
