#ifndef __RYN_GRAPHICS_COLOR_HPP__
#define __RYN_GRAPHICS_COLOR_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    struct Color
    {
        f32 R;
        f32 G;
        f32 B;
        f32 A;

        constexpr Color(f32 r, f32 g, f32 b, f32 a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
    };

    struct Colors
    {
        static constexpr Color Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
        static constexpr Color White = Color(1.0f, 1.0f, 1.0f, 1.0f);
        static constexpr Color Red  = Color(0.8f, 0.0f, 0.0f, 1.0f);
        static constexpr Color Orange = Color(0.8f, 0.4f, 0.0f, 1.0f);
        static constexpr Color Yellow = Color(0.8f, 0.8f, 0.0f, 1.0f);
        static constexpr Color Lime = Color(0.4f, 0.8f, 0.0f, 1.0f);
        static constexpr Color Green = Color(0.0f, 0.8f, 0.0f, 1.0f);
        static constexpr Color Teal = Color(0.0f, 0.8f, 0.4f, 1.0f);
        static constexpr Color Cyan = Color(0.0f, 0.8f, 0.8f, 1.0f);
        static constexpr Color Azure = Color(0.0f, 0.4f, 0.8f, 1.0f);
        static constexpr Color Blue = Color(0.0f, 0.0f, 0.8f, 1.0f);
        static constexpr Color Violet = Color(0.4f, 0.0f, 0.8f, 1.0f);
        static constexpr Color Magenta = Color(0.8f, 0.0f, 0.8f, 1.0f);
        static constexpr Color Pink = Color(0.8f, 0.0f, 0.4f, 1.0f);
    };
}

#endif