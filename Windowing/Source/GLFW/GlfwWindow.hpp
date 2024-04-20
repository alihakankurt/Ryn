#ifndef __RYN_WINDOWING_GLFW_GLFW_WINDOW_HPP__
#define __RYN_WINDOWING_GLFW_GLFW_WINDOW_HPP__

#include <Ryn/Native/GLFW.hpp>
#include <Ryn/Windowing/Window.hpp>

#include "Input/GlfwInputContext.hpp"

namespace Ryn
{
    class GlfwWindow : public Window
    {
      private:
        GLFW::Window _handle;
        GlfwInputContext* _inputContext;

      public:
        GlfwWindow(const WindowConfig& config);
        ~GlfwWindow();

        void Close() override;
        void Update() override;
        void Present() override;
        bool IsActive() const override;

        InputContext* GetInputContext() override;
    };
}

#endif