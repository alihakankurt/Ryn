#include <Ryn/Native/GLFW.hpp>

#include "GLFW/GlfwWindow.hpp"

namespace Ryn
{
    GlfwWindow::GlfwWindow(const WindowConfig& config)
    {
        GLFW::Initialize();
        
        GLFW::WindowHint(GLFW::WindowHints::ClientAPI, +GLFW::ClientAPI::OpenGL);
        GLFW::WindowHint(GLFW::WindowHints::ContextVersionMajor, 4);
        GLFW::WindowHint(GLFW::WindowHints::ContextVersionMinor, 1);

        _handle = GLFW::CreateWindow(As<i32>(config.Width), As<i32>(config.Height), config.Title, nullptr, nullptr);
        GLFW::MakeContextCurrent(_handle);
    }

    GlfwWindow::~GlfwWindow()
    {
        GLFW::DestroyWindow(_handle);
        GLFW::Terminate();
    }

    void GlfwWindow::Update()
    {
        GLFW::SwapBuffers(_handle);
        GLFW::PollEvents();
    }

    bool GlfwWindow::IsActive() const
    {
        return !GLFW::WindowShouldClose(_handle);
    }
}
