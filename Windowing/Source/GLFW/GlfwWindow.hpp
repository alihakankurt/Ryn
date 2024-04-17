#ifndef __RYN_WINDOWING_GLFW_GLFW_WINDOW_HPP__
#define __RYN_WINDOWING_GLFW_GLFW_WINDOW_HPP__

#include <Ryn/Native/GLFW.hpp>
#include <Ryn/Windowing/Window.hpp>

namespace Ryn
{
    class GlfwWindow : public Window
    {
      private:
        GLFW::Window _handle;

      public:
        GlfwWindow(const WindowConfig& config);
        ~GlfwWindow();

        void Update() override;
        bool IsActive() const override;
    };
}

#endif