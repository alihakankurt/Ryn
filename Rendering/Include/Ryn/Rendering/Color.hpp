#ifndef __RYN_RENDERING_COLOR_HPP__
#define __RYN_RENDERING_COLOR_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    struct Color
    {
        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Orange;
        static const Color Yellow;
        static const Color Lime;
        static const Color Green;
        static const Color Teal;
        static const Color Cyan;
        static const Color Azure;
        static const Color Blue;
        static const Color Violet;
        static const Color Magenta;
        static const Color Pink;

        f32 R;
        f32 G;
        f32 B;
        f32 A;

        Color(f32 r, f32 g, f32 b, f32 a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
    };
}

#endif