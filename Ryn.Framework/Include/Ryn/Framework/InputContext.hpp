#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Collections/Array.hpp>
#include <Ryn/Mathematics/Vector2.hpp>
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
        Array<KeyState, +Key::Count> _keys;
        Array<MouseButtonState, +MouseButton::Count> _mouseButtons;
        Vector2<f64> _mousePosition;

      public:
        InputContext() :
            _keys{KeyState::Up},
            _mouseButtons{MouseButtonState::Up} {}

        template <KeyState... TStates>
        bool IsKey(Key key) const
        {
            return ((_keys[+key] == TStates) || ...);
        }

        bool IsKeyUp(Key key) const { return IsKey<KeyState::Up, KeyState::Released>(key); }
        bool IsKeyDown(Key key) const { return IsKey<KeyState::Down, KeyState::Pressed>(key); }
        bool IsKeyPressed(Key key) const { return IsKey<KeyState::Pressed>(key); }
        bool IsKeyReleased(Key key) const { return IsKey<KeyState::Released>(key); }

        template <MouseButtonState... TStates>
        bool IsMouseButton(MouseButton button) const
        {
            return ((_mouseButtons[+button] == TStates) || ...);
        }

        bool IsMouseButtonUp(MouseButton button) const { return IsMouseButton<MouseButtonState::Up, MouseButtonState::Released>(button); }
        bool IsMouseButtonDown(MouseButton button) const { return IsMouseButton<MouseButtonState::Down, MouseButtonState::Pressed>(button); }
        bool IsMouseButtonPressed(MouseButton button) const { return IsMouseButton<MouseButtonState::Pressed>(button); }
        bool IsMouseButtonReleased(MouseButton button) const { return IsMouseButton<MouseButtonState::Released>(button); }

        Vector2<f64> MousePosition() const { return _mousePosition; }

      private:
        friend class Game;

        void SetKeyState(Key key, KeyState state) { _keys[+key] = state; }
        void SetMouseButtonState(MouseButton button, MouseButtonState state) { _mouseButtons[+button] = state; }
        void SetMousePosition(Vector2<f64> position) { _mousePosition = position; }

        void Update();
    };
}
