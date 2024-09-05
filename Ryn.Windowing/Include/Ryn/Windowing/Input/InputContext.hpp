#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Windowing/Input/Key.hpp>
#include <Ryn/Windowing/Input/MouseButton.hpp>

namespace Ryn
{
    class InputContext
    {
      private:
        KeyState _keys[static_cast<u32>(Key::Count)] = {KeyState::Up};
        MouseButtonState _mouseButtons[static_cast<u32>(MouseButton::Count)] = {MouseButtonState::Up};

      public:
        bool IsKeyUp(Key key) const;
        bool IsKeyDown(Key key) const;
        bool IsKeyPressed(Key key) const;
        bool IsKeyReleased(Key key) const;

        KeyState GetKeyState(Key key) const;
        void SetKeyState(Key key, KeyState state);

        bool IsButtonUp(MouseButton button) const;
        bool IsButtonDown(MouseButton button) const;
        bool IsButtonPressed(MouseButton button) const;
        bool IsButtonReleased(MouseButton button) const;

        MouseButtonState GetButtonState(MouseButton button) const;
        void SetButtonState(MouseButton button, MouseButtonState state);

        void Update();
    };
}
