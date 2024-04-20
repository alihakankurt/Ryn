#include "GLFW/Input/GlfwInputContext.hpp"

namespace Ryn
{
    GlfwInputContext::GlfwInputContext(GLFW::Window window)
    {
        GLFW::SetWindowUserPointer(window, this);
        GLFW::SetKeyCallback(window, OnKeyEvent);
        GLFW::SetMouseButtonCallback(window, OnMouseButtonEvent);
    }

    void GlfwInputContext::Update()
    {
        for (Key key : _keyUpdates)
            UpdateState(_keyStates[+key]);

        _keyUpdates.Clear();

        for (MouseButton mouseButton : _mouseButtonUpdates)
            UpdateState(_mouseButtonStates[+mouseButton]);

        _mouseButtonUpdates.Clear();
    }

    bool GlfwInputContext::IsKeyUp(Key key) const
    {
        InputState state = _keyStates[+key];
        return state == InputState::Up || state == InputState::Released;
    }

    bool GlfwInputContext::IsKeyDown(Key key) const
    {
        InputState state = _keyStates[+key];
        return state == InputState::Down || state == InputState::Pressed;
    }

    bool GlfwInputContext::IsKeyPressed(Key key) const
    {
        InputState state = _keyStates[+key];
        return state == InputState::Pressed;
    }

    bool GlfwInputContext::IsKeyReleased(Key key) const
    {
        InputState state = _keyStates[+key];
        return state == InputState::Released;
    }

    bool GlfwInputContext::IsMouseButtonUp(MouseButton mouseButton) const
    {
        InputState state = _mouseButtonStates[+mouseButton];
        return state == InputState::Up || state == InputState::Released;
    }

    bool GlfwInputContext::IsMouseButtonDown(MouseButton mouseButton) const
    {
        InputState state = _mouseButtonStates[+mouseButton];
        return state == InputState::Down || state == InputState::Pressed;
    }

    bool GlfwInputContext::IsMouseButtonPressed(MouseButton mouseButton) const
    {
        InputState state = _mouseButtonStates[+mouseButton];
        return state == InputState::Pressed;
    }

    bool GlfwInputContext::IsMouseButtonReleased(MouseButton mouseButton) const
    {
        InputState state = _mouseButtonStates[+mouseButton];
        return state == InputState::Released;
    }

    void GlfwInputContext::UpdateState(InputState& state)
    {
        if (state == InputState::Pressed)
            state = InputState::Down;
        else if (state == InputState::Released)
            state = InputState::Up;
    }

    void GlfwInputContext::OnKeyEvent(GLFW::Window window, GLFW::Key glfwKey, i32 scancode, GLFW::InputAction action, GLFW::InputModifiers modifiers)
    {
        GlfwInputContext* input = As<GlfwInputContext*>(GLFW::GetWindowUserPointer(window));
        if (!input)
            return;

        Key key = As<Key>(glfwKey);
        if (key == Key::Unknown)
            return;

        switch (action)
        {
            case GLFW::InputAction::Release:
                input->_keyStates[+key] = InputState::Released;
                input->_keyUpdates.Add(key);
                break;
            case GLFW::InputAction::Press:
                input->_keyStates[+key] = InputState::Pressed;
                input->_keyUpdates.Add(key);
                break;
        }
    }

    void GlfwInputContext::OnMouseButtonEvent(GLFW::Window window, GLFW::MouseButton glfwMouseButton, GLFW::InputAction action, GLFW::InputModifiers modifiers)
    {
        GlfwInputContext* input = As<GlfwInputContext*>(GLFW::GetWindowUserPointer(window));
        if (!input)
            return;

        MouseButton mouseButton = As<MouseButton>(glfwMouseButton);
        switch (action)
        {
            case GLFW::InputAction::Release:
                input->_mouseButtonStates[+mouseButton] = InputState::Released;
                input->_mouseButtonUpdates.Add(mouseButton);
                break;
            case GLFW::InputAction::Press:
                input->_mouseButtonStates[+mouseButton] = InputState::Pressed;
                input->_mouseButtonUpdates.Add(mouseButton);
                break;
        }
    }
}
