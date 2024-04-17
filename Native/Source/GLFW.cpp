#include <Ryn/Native/GLFW.hpp>
#include <Ryn/Native/Platform.hpp>
#include <stdio.h>

#if RYN_PLATFORM_WINDOWS
#define GLFW_PATH "glfw3.dll"
#elif RYN_PLATFORM_LINUX
#define GLFW_PATH "libglfw.3.so"
#elif RYN_PLATFORM_MACOS
#define GLFW_PATH "libglfw.3.dylib"
#endif

namespace Ryn::GLFW
{
    InitializeFunction Initialize;
    TerminateFunction Terminate;
#if RYN_DEBUG
    SetErrorCallbackFunction SetErrorCallback;
#endif
    WindowHintFunction WindowHint;
    CreateWindowFunction CreateWindow;
    DestroyWindowFunction DestroyWindow;
    MakeContextCurrentFunction MakeContextCurrent;
    PollEventsFunction PollEvents;
    SwapBuffersFunction SwapBuffers;
    WindowShouldCloseFunction WindowShouldClose;

    Platform::Module Handle;

    bool Load()
    {
        Handle = Platform::LoadModule(GLFW_PATH);
        if (!Handle)
            return false;

        Initialize = Platform::LoadFunction<InitializeFunction>(Handle, "glfwInit");
        Terminate = Platform::LoadFunction<TerminateFunction>(Handle, "glfwTerminate");
#if RYN_DEBUG
        SetErrorCallback = Platform::LoadFunction<SetErrorCallbackFunction>(Handle, "glfwSetErrorCallback");

        SetErrorCallback([](ErrorCode error, const char* description)
        {
            printf("GLFW Error: %d - %s\n", +error, description);
        });
#endif
        WindowHint = Platform::LoadFunction<WindowHintFunction>(Handle, "glfwWindowHint");
        CreateWindow = Platform::LoadFunction<CreateWindowFunction>(Handle, "glfwCreateWindow");
        DestroyWindow = Platform::LoadFunction<DestroyWindowFunction>(Handle, "glfwDestroyWindow");
        MakeContextCurrent = Platform::LoadFunction<MakeContextCurrentFunction>(Handle, "glfwMakeContextCurrent");
        PollEvents = Platform::LoadFunction<PollEventsFunction>(Handle, "glfwPollEvents");
        SwapBuffers = Platform::LoadFunction<SwapBuffersFunction>(Handle, "glfwSwapBuffers");
        WindowShouldClose = Platform::LoadFunction<WindowShouldCloseFunction>(Handle, "glfwWindowShouldClose");

        return true;
    }

    void Unload()
    {
        if (!Handle)
            return;

        Platform::FreeModule(Handle);
        Handle = nullptr;
    }
}