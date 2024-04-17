#include <Ryn/Native/OpenGL.hpp>
#include <Ryn/Native/Platform.hpp>

#if RYN_PLATFORM_WINDOWS
#define OPENGL_PATH "opengl32.dll"
#elif RYN_PLATFORM_LINUX
#define OPENGL_PATH "libGL.so"
#elif RYN_PLATFORM_MACOS
#define OPENGL_PATH "/System/Library/Frameworks/OpenGL.framework/OpenGL"
#endif

namespace Ryn::OpenGL
{
    ClearFunction Clear;
    ClearColorFunction ClearColor;

    Platform::Module Handle;

    bool Load()
    {
        Handle = Platform::LoadModule(OPENGL_PATH);
        if (!Handle)
            return false;

        Clear = Platform::LoadFunction<ClearFunction>(Handle, "glClear");
        ClearColor = Platform::LoadFunction<ClearColorFunction>(Handle, "glClearColor");

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