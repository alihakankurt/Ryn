#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    enum class Key
    {
        Unknown,

        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,

        Space,
        Enter,
        Escape,
        Backspace,
        Tab,

        Left,
        Right,
        Down,
        Up,

        Tilde,
        Minus,
        Equal,
        LeftBracket,
        RightBracket,
        Semicolon,
        Quote,
        Backslash,
        Backtick,
        Comma,
        Period,
        Slash,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        Count,
    };

    constexpr u32 operator+(Key key) { return static_cast<u32>(key); }
}
