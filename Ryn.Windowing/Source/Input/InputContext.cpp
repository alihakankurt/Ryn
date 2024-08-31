#include <Ryn/Windowing/Input/InputContext.hpp>

namespace Ryn::Windowing::Input
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
        return _keys[static_cast<Core::usz>(key)];
    }

    void InputContext::SetKeyState(Key key, KeyState state)
    {
        _keys[static_cast<Core::usz>(key)] = state;
    }

    void InputContext::Update()
    {
        for (KeyState& state : _keys)
        {
            if (state == KeyState::Pressed)
            {
                state = KeyState::Down;
            }
            else if (state == KeyState::Released)
            {
                state = KeyState::Up;
            }
        }
    }
}
