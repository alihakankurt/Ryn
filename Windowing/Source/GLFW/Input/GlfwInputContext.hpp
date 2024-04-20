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
        InputState _keyStates[+Key::Count] = { InputState::Up };
        List<Key> _keyUpdates;

      public:
        GlfwInputContext(GLFW::Window window);
        ~GlfwInputContext() override = default;

        void Update();

        bool IsKeyUp(Key key) const override;
        bool IsKeyDown(Key key) const override;
        bool IsKeyPressed(Key key) const override;
        bool IsKeyReleased(Key key) const override;

      private:
        static void OnKeyEvent(GLFW::Window window, GLFW::Keys key, i32 scancode, GLFW::KeyAction action, GLFW::KeyModifiers modifiers);
    };
}

#endif