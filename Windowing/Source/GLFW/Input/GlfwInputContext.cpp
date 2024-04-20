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
        for (Keys key : _keyUpdates)
        {
            InputState& state = _keyStates[+key];
            if (state == InputState::Pressed)
                state = InputState::Down;
            else if (state == InputState::Released)
                state = InputState::Up;
        }

        _keyUpdates.Clear();
    }

    bool GlfwInputContext::IsKeyUp(Keys key) const
    {
        InputState state = _keyStates[+key];
        return state == InputState::Up || state == InputState::Released;
    }

    bool GlfwInputContext::IsKeyDown(Keys key) const
    {
        InputState state = _keyStates[+key];
        return state == InputState::Down || state == InputState::Pressed;
    }

    bool GlfwInputContext::IsKeyPressed(Keys key) const
    {
        InputState state = _keyStates[+key];
        return state == InputState::Pressed;
    }

    bool GlfwInputContext::IsKeyReleased(Keys key) const
    {
        InputState state = _keyStates[+key];
        return state == InputState::Released;
    }

    void GlfwInputContext::OnKeyEvent(GLFW::Window window, GLFW::Keys glfwKey, i32 scancode, GLFW::KeyAction action, GLFW::KeyModifiers modifiers)
    {
        GlfwInputContext* input = As<GlfwInputContext*>(GLFW::GetWindowUserPointer(window));
        if (!input)
            return;

        Keys key = As<Keys>(glfwKey);
        if (key == Keys::Unknown)
            return;

        switch (action)
        {
            case GLFW::KeyAction::Release:
                input->_keyStates[+key] = InputState::Released;
                input->_keyUpdates.Add(key);
                break;
            case GLFW::KeyAction::Press:
                input->_keyStates[+key] = InputState::Pressed;
                input->_keyUpdates.Add(key);
                break;
            case GLFW::KeyAction::Repeat:
                break;
        }
    }
}
