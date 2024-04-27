#include <Ryn/Windowing/Window.hpp>

#include "GLFW/GlfwWindow.hpp"

namespace Ryn
{
    Ref<Window> Window::Create(const WindowConfig& config)
    {
        return Ref<Window>(new GlfwWindow(config));
    }
}
