#include "GLFW/Input/GlfwInputContext.hpp"

namespace Ryn
{
    GlfwInputContext::GlfwInputContext(GLFW::Window window)
    {
        GLFW::SetWindowUserPointer(window, this);
        GLFW::SetKeyCallback(window, OnKeyEvent);
    }

    void GlfwInputContext::Update()
    {
        for (auto& keyState : _keyStates)
        {
            if (keyState == InputState::Pressed)
                keyState = InputState::Down;
            else if (keyState == InputState::Released)
                keyState = InputState::Up;
        }
    }

    bool GlfwInputContext::IsKeyUp(Keys key) const
    {
        return _keyStates[+key] == InputState::Up;
    }

    bool GlfwInputContext::IsKeyDown(Keys key) const
    {
        return _keyStates[+key] == InputState::Down;
    }

    bool GlfwInputContext::IsKeyPressed(Keys key) const
    {
        return _keyStates[+key] == InputState::Pressed;
    }

    bool GlfwInputContext::IsKeyReleased(Keys key) const
    {
        return _keyStates[+key] == InputState::Released;
    }

    void GlfwInputContext::OnKeyEvent(GLFW::Window window, GLFW::Keys key, i32 scancode, GLFW::KeyAction action, GLFW::KeyModifiers modifiers)
    {
        GlfwInputContext* input = As<GlfwInputContext*>(GLFW::GetWindowUserPointer(window));
        if (!input)
            return;

        switch (action)
        {
            case GLFW::KeyAction::Release:
                input->_keyStates[+key] = InputState::Released;
                break;
            case GLFW::KeyAction::Press:
                input->_keyStates[+key] = InputState::Pressed;
                break;
            case GLFW::KeyAction::Repeat:
                break;
        }
    }
}
