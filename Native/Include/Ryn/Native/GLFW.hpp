#ifndef __RYN_NATIVE_GLFW_HPP__
#define __RYN_NATIVE_GLFW_HPP__

#include <Ryn/Core.hpp>

namespace Ryn::GLFW
{
    enum struct WindowHints : i32
    {
        Focused = 0x0002'0001,
        Iconified = 0x0002'0002,
        Resizable = 0x0002'0003,
        Visible = 0x0002'0004,
        Decorated = 0x0002'0005,
        AutoIconify = 0x0002'0006,
        Floating = 0x0002'0007,
        Maximized = 0x0002'0008,
        CenterCursor = 0x0002'0009,
        TransparentFramebuffer = 0x0002'000A,
        Hovered = 0x0002'000B,
        FocusOnShow = 0x0002'000C,
        MousePassthrough = 0x0002'000D,
        PositionX = 0x0002'000E,
        PositionY = 0x0002'000F,
        RedBits = 0x0002'1001,
        GreenBits = 0x0002'1002,
        BlueBits = 0x0002'1003,
        AlphaBits = 0x0002'1004,
        DepthBits = 0x0002'1005,
        StencilBits = 0x0002'1006,
        AccumRedBits = 0x0002'1007,
        AccumGreenBits = 0x0002'1008,
        AccumBlueBits = 0x0002'1009,
        AccumAlphaBits = 0x0002'100A,
        AuxBuffers = 0x0002'100B,
        Stereo = 0x0002'100C,
        Samples = 0x0002'100D,
        SRGBCapable = 0x0002'100E,
        RefreshRate = 0x0002'100F,
        DoubleBuffer = 0x0002'1010,
        ClientAPI = 0x0002'2001,
        ContextVersionMajor = 0x0002'2002,
        ContextVersionMinor = 0x0002'2003,
        ContextRevision = 0x0002'2004,
        ContextRobustness = 0x0002'2005,
        OpenGLForwardCompat = 0x0002'2006,
        DebugContext = 0x0002'2007,
        OpenGLProfile = 0x0002'2008,
        ContextReleaseBehavior = 0x0002'2009,
        ContextNoError = 0x0002'200A,
        ContextCreationAPI = 0x0002'200B,
        ScaleToMonitor = 0x0002'200C,
        ScaleToFrameBuffer = 0x0002'200D,
        CocoaRetinaFramebuffer = 0x0002'3001,
        CocoaFrameName = 0x0002'3002,
        CocoaGraphicsSwitching = 0x0002'3003,
        X11ClassName = 0x0002'4001,
        X11InstanceName = 0x0002'4002,
        Win32KeyboardMenu = 0x0002'5001,
        Win32ShowDefault = 0x0002'5002,
        WaylandAppId = 0x0002'6001,
    };

    enum struct ClientAPI : i32
    {
        NoAPI = 0,
        OpenGL = 0x0003'0001,
        OpenGLES = 0x0003'0002,
    };

    enum struct ContextRobustness : i32
    {
        NoRobustness = 0,
        NoResetNotification = 0x0003'1001,
        LoseContextOnReset = 0x0003'1002,
    };

    enum struct OpenGLProfile : i32
    {
        Any = 0,
        Core = 0x0003'2001,
        Compatibility = 0x0003'2002,
    };

    enum struct ContextReleaseBehavior : i32
    {
        Any = 0,
        Flush = 0x0003'5001,
        None = 0x0003'5002,
    };

    enum struct ContextCreationAPI : i32
    {
        Native = 0x0003'6001,
        EGL = 0x0003'6002,
        OSMesa = 0x0003'6003,
    };

    enum struct ErrorCode : i32
    {
        NotInitialized = 0x0001'0001,
        NoCurrentContext = 0x0001'0002,
        InvalidEnum = 0x0001'0003,
        InvalidValue = 0x0001'0004,
        OutOfMemory = 0x0001'0005,
        APIUnavailable = 0x0001'0006,
        VersionUnavailable = 0x0001'0007,
        PlatformError = 0x0001'0008,
        FormatUnavailable = 0x0001'0009,
        NoWindowContext = 0x0001'000A,
    };

    using Window = void*;

    using InitializeFunction = bool (*)();
    extern InitializeFunction Initialize;

    using TerminateFunction = void (*)();
    extern TerminateFunction Terminate;

    using ErrorCallback = void (*)(ErrorCode error, cstring description);
    using SetErrorCallbackFunction = ErrorCallback (*)(ErrorCallback callback);
    extern SetErrorCallbackFunction SetErrorCallback;

    using WindowHintFunction = void (*)(WindowHints hint, i32 value);
    extern WindowHintFunction WindowHint;

    using CreateWindowFunction = Window (*)(i32 width, i32 height, cstring title, void* monitor, void* share);
    extern CreateWindowFunction CreateWindow;

    using DestroyWindowFunction = void (*)(Window window);
    extern DestroyWindowFunction DestroyWindow;

    using MakeContextCurrentFunction = void (*)(Window window);
    extern MakeContextCurrentFunction MakeContextCurrent;

    using PollEventsFunction = void (*)();
    extern PollEventsFunction PollEvents;

    using SwapBuffersFunction = void (*)(Window window);
    extern SwapBuffersFunction SwapBuffers;

    using WindowShouldCloseFunction = bool (*)(Window window);
    extern WindowShouldCloseFunction WindowShouldClose;

    bool Load();
    void Unload();
}

#endif