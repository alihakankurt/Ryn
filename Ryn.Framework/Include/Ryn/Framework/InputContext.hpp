#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Collections/Array.hpp>
#include <Ryn/Windowing/Input/Key.hpp>
#include <Ryn/Windowing/Input/MouseButton.hpp>

namespace Ryn
{
    enum class KeyState
    {
        Up,
        Down,
        Pressed,
        Released
    };

    enum class MouseButtonState
    {
        Up,
        Down,
        Pressed,
        Released
    };

    class InputContext
    {
      private:
        Array<KeyState, +Key::Count> _keys = {KeyState::Up};
        Array<MouseButtonState, +MouseButton::Count> _mouseButtons = {MouseButtonState::Up};

      public:
        bool IsKeyUp(Key key) const;
        bool IsKeyDown(Key key) const;
        bool IsKeyPressed(Key key) const;
        bool IsKeyReleased(Key key) const;

        KeyState GetKeyState(Key key) const;

        bool IsMouseButtonUp(MouseButton button) const;
        bool IsMouseButtonDown(MouseButton button) const;
        bool IsMouseButtonPressed(MouseButton button) const;
        bool IsMouseButtonReleased(MouseButton button) const;

        MouseButtonState GetMouseButtonState(MouseButton button) const;

      private:
        friend class Game;
        void SetKeyState(Key key, KeyState state);
        void SetMouseButtonState(MouseButton button, MouseButtonState state);
        void Update();
    };
}
