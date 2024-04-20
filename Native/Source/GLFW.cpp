#include <Ryn/Native/GLFW.hpp>
#include <Ryn/Native/Platform.hpp>

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
    SetErrorCallbackFunction SetErrorCallback;

    WindowHintFunction WindowHint;
    CreateWindowFunction CreateWindow;
    DestroyWindowFunction DestroyWindow;

    SetWindowUserPointerFunction SetWindowUserPointer;
    GetWindowUserPointerFunction GetWindowUserPointer;

    MakeContextCurrentFunction MakeContextCurrent;

    WindowShouldCloseFunction WindowShouldClose;
    SetWindowShouldCloseFunction SetWindowShouldClose;

    PollEventsFunction PollEvents;
    SwapBuffersFunction SwapBuffers;

    SetKeyCallbackFunction SetKeyCallback;
    SetMouseButtonCallbackFunction SetMouseButtonCallback;
    SetMousePositionCallbackFunction SetMousePositionCallback;
    GetMousePositionFunction GetMousePosition;

    Platform::Module Handle;

    bool Load()
    {
        Handle = Platform::LoadModule(GLFW_PATH);
        if (!Handle)
            return false;

        Initialize = Platform::LoadFunction<InitializeFunction>(Handle, "glfwInit");
        Terminate = Platform::LoadFunction<TerminateFunction>(Handle, "glfwTerminate");
        SetErrorCallback = Platform::LoadFunction<SetErrorCallbackFunction>(Handle, "glfwSetErrorCallback");

        WindowHint = Platform::LoadFunction<WindowHintFunction>(Handle, "glfwWindowHint");
        CreateWindow = Platform::LoadFunction<CreateWindowFunction>(Handle, "glfwCreateWindow");
        DestroyWindow = Platform::LoadFunction<DestroyWindowFunction>(Handle, "glfwDestroyWindow");

        SetWindowUserPointer = Platform::LoadFunction<SetWindowUserPointerFunction>(Handle, "glfwSetWindowUserPointer");
        GetWindowUserPointer = Platform::LoadFunction<GetWindowUserPointerFunction>(Handle, "glfwGetWindowUserPointer");

        MakeContextCurrent = Platform::LoadFunction<MakeContextCurrentFunction>(Handle, "glfwMakeContextCurrent");

        WindowShouldClose = Platform::LoadFunction<WindowShouldCloseFunction>(Handle, "glfwWindowShouldClose");
        SetWindowShouldClose = Platform::LoadFunction<SetWindowShouldCloseFunction>(Handle, "glfwSetWindowShouldClose");

        PollEvents = Platform::LoadFunction<PollEventsFunction>(Handle, "glfwPollEvents");
        SwapBuffers = Platform::LoadFunction<SwapBuffersFunction>(Handle, "glfwSwapBuffers");

        SetKeyCallback = Platform::LoadFunction<SetKeyCallbackFunction>(Handle, "glfwSetKeyCallback");
        SetMouseButtonCallback = Platform::LoadFunction<SetMouseButtonCallbackFunction>(Handle, "glfwSetMouseButtonCallback");
        SetMousePositionCallback = Platform::LoadFunction<SetMousePositionCallbackFunction>(Handle, "glfwSetCursorPosCallback");
        GetMousePosition = Platform::LoadFunction<GetMousePositionFunction>(Handle, "glfwGetCursorPos");


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