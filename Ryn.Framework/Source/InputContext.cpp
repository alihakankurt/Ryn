#include <Ryn/Framework/InputContext.hpp>

namespace Ryn
{
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
