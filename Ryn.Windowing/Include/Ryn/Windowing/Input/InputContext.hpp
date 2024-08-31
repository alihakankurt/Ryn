#pragma once

#include <Ryn/Core.hpp>
#include <Ryn/Windowing/Input/Key.hpp>
#include <Ryn/Windowing/Input/MouseButton.hpp>

namespace Ryn::Windowing::Input
{
    class InputContext
    {
      private:
        KeyState _keys[static_cast<Core::usz>(Key::Count)] = {KeyState::Up};
        MouseButtonState _mouseButtons[static_cast<Core::usz>(MouseButton::Count)] = {MouseButtonState::Up};

      public:
        bool IsKeyUp(Key key) const;
        bool IsKeyDown(Key key) const;
        bool IsKeyPressed(Key key) const;
        bool IsKeyReleased(Key key) const;

        KeyState GetKeyState(Key key) const;
        void SetKeyState(Key key, KeyState state);

        bool IsMouseButtonUp(MouseButton button) const;
        bool IsMouseButtonDown(MouseButton button) const;
        bool IsMouseButtonPressed(MouseButton button) const;
        bool IsMouseButtonReleased(MouseButton button) const;

        MouseButtonState GetMouseButtonState(MouseButton button) const;
        void SetMouseButtonState(MouseButton button, MouseButtonState state);

        void Update();
    };
}
