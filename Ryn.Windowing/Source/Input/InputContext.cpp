#include <Ryn/Windowing/Input/InputContext.hpp>

namespace Ryn
{
    bool InputContext::IsKeyUp(Key key) const
    {
        KeyState state = GetKeyState(key);
        return state == KeyState::Up || state == KeyState::Released;
    }

    bool InputContext::IsKeyDown(Key key) const
    {
        KeyState state = GetKeyState(key);
        return state == KeyState::Down || state == KeyState::Pressed;
    }

    bool InputContext::IsKeyPressed(Key key) const
    {
        KeyState state = GetKeyState(key);
        return state == KeyState::Pressed;
    }

    bool InputContext::IsKeyReleased(Key key) const
    {
        KeyState state = GetKeyState(key);
        return state == KeyState::Released;
    }

    KeyState InputContext::GetKeyState(Key key) const
    {
        return _keys[static_cast<u32>(key)];
    }

    void InputContext::SetKeyState(Key key, KeyState state)
    {
        _keys[static_cast<u32>(key)] = state;
    }

    bool InputContext::IsButtonUp(MouseButton button) const
    {
        MouseButtonState state = GetButtonState(button);
        return state == MouseButtonState::Up || state == MouseButtonState::Released;
    }

    bool InputContext::IsButtonDown(MouseButton button) const
    {
        MouseButtonState state = GetButtonState(button);
        return state == MouseButtonState::Down || state == MouseButtonState::Pressed;
    }

    bool InputContext::IsButtonPressed(MouseButton button) const
    {
        MouseButtonState state = GetButtonState(button);
        return state == MouseButtonState::Pressed;
    }

    bool InputContext::IsButtonReleased(MouseButton button) const
    {
        MouseButtonState state = GetButtonState(button);
        return state == MouseButtonState::Released;
    }

    MouseButtonState InputContext::GetButtonState(MouseButton button) const
    {
        return _mouseButtons[static_cast<u32>(button)];
    }

    void InputContext::SetButtonState(MouseButton button, MouseButtonState state)
    {
        _mouseButtons[static_cast<u32>(button)] = state;
    }

    void InputContext::Update()
    {
        for (KeyState& state : _keys)
        {
            if (state == KeyState::Pressed)
                state = KeyState::Down;
            else if (state == KeyState::Released)
                state = KeyState::Up;
        }

        for (MouseButtonState& state : _mouseButtons)
        {
            if (state == MouseButtonState::Pressed)
                state = MouseButtonState::Down;
            else if (state == MouseButtonState::Released)
                state = MouseButtonState::Up;
        }
    }
}
