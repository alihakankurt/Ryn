#pragma once

namespace Ryn
{
    enum class MouseButtonState
    {
        Up,
        Down,
        Pressed,
        Released,
    };

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
}
