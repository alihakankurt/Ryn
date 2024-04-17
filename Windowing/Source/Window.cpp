#include <Ryn/Windowing/Window.hpp>

#include "GLFW/GlfwWindow.hpp"

namespace Ryn
{
    Window* Window::Create(const WindowConfig& config)
    {
        return new GlfwWindow(config);
    }
}
