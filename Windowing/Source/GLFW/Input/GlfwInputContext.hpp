#ifndef __RYN_WINDOWING_SOURCE_GLFW_INPUT_GLFW_INPUT_CONTEXT_HPP__
#define __RYN_WINDOWING_SOURCE_GLFW_INPUT_GLFW_INPUT_CONTEXT_HPP__

#include <Ryn/Native/GLFW.hpp>
#include <Ryn/Windowing/Input/InputState.hpp>
#include <Ryn/Windowing/Input/InputContext.hpp>
#include <Ryn/Collections.hpp>

namespace Ryn
{
    class GlfwInputContext : public InputContext
    {
      private:
        InputState _keyStates[+Key::Count] = {InputState::Up};
        List<Key> _keyUpdates;

        InputState _mouseButtonStates[+MouseButton::Count] = {InputState::Up};
        List<MouseButton> _mouseButtonUpdates;

        Vector2<f64> _mousePosition;

      public:
        GlfwInputContext(GLFW::Window window);
        ~GlfwInputContext() override = default;

        void Update();

        bool IsKeyUp(Key key) const override;
        bool IsKeyDown(Key key) const override;
        bool IsKeyPressed(Key key) const override;
        bool IsKeyReleased(Key key) const override;

        bool IsMouseButtonUp(MouseButton mouseButton) const override;
        bool IsMouseButtonDown(MouseButton mouseButton) const override;
        bool IsMouseButtonPressed(MouseButton mouseButton) const override;
        bool IsMouseButtonReleased(MouseButton mouseButton) const override;

        inline Vector2<f64> GetMousePosition() const override;

      private:
        static inline void UpdateState(InputState& state);

        static void OnKeyEvent(GLFW::Window window, GLFW::Key glfwKey, i32 scancode, GLFW::InputAction action, GLFW::InputModifiers modifiers);
        static void OnMouseButtonEvent(GLFW::Window window, GLFW::MouseButton glfwMouseButton, GLFW::InputAction action, GLFW::InputModifiers modifiers);
        static void OnMousePositionEvent(GLFW::Window window, f64 x, f64 y);
    };
}

#endif