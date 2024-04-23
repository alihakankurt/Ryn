#include "GLFW/GlfwWindow.hpp"

namespace Ryn
{
    GlfwWindow::GlfwWindow(const WindowConfig& config)
    {
        GLFW::WindowHint(GLFW::WindowHints::ClientAPI, +GLFW::ClientAPI::OpenGL);
        GLFW::WindowHint(GLFW::WindowHints::ContextVersionMajor, 4);
        GLFW::WindowHint(GLFW::WindowHints::ContextVersionMinor, 1);

        _handle = GLFW::CreateWindow(As<i32>(config.Width), As<i32>(config.Height), config.Title.Data(), nullptr, nullptr);
        GLFW::MakeContextCurrent(_handle);

        _inputContext = new GlfwInputContext(_handle);
    }

    GlfwWindow::~GlfwWindow()
    {
        delete _inputContext;
        GLFW::DestroyWindow(_handle);
    }

    void GlfwWindow::Close()
    {
        GLFW::SetWindowShouldClose(_handle, true);
    }

    void GlfwWindow::Update()
    {
        _inputContext->Update();
        GLFW::PollEvents();
    }

    void GlfwWindow::Present()
    {
        GLFW::SwapBuffers(_handle);
    }

    bool GlfwWindow::IsActive() const
    {
        return !GLFW::WindowShouldClose(_handle);
    }

    InputContext* GlfwWindow::GetInputContext()
    {
        return _inputContext;
    }
}
