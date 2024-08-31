#pragma once

#include <Ryn/Core.hpp>
#include <Ryn/Windowing/Input/Key.hpp>

namespace Ryn::Windowing::Input
{
    class InputContext
    {
      private:
        KeyState _keys[static_cast<Core::usz>(Key::Count)] = {KeyState::Up};

      public:
        bool IsKeyUp(Key key) const
        {
            KeyState state = GetKeyState(key);
            return state == KeyState::Up || state == KeyState::Released;
        }

        bool IsKeyDown(Key key) const
        {
            KeyState state = GetKeyState(key);
            return state == KeyState::Down || state == KeyState::Pressed;
        }

        bool IsKeyPressed(Key key) const
        {
            KeyState state = GetKeyState(key);
            return state == KeyState::Pressed;
        }

        bool IsKeyReleased(Key key) const
        {
            KeyState state = GetKeyState(key);
            return state == KeyState::Released;
        }

        KeyState GetKeyState(Key key) const
        {
            return _keys[static_cast<Core::usz>(key)];
        }

        void SetKeyState(Key key, KeyState state)
        {
            _keys[static_cast<Core::usz>(key)] = state;
        }

        void Update()
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
    };
}
