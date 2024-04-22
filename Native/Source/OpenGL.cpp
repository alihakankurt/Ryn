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

    CreateVertexArrayFunction CreateVertexArray;
    DeleteVertexArrayFunction DeleteVertexArray;
    BindVertexArrayFunction BindVertexArray;

    CreateBufferFunction CreateBuffer;
    DeleteBufferFunction DeleteBuffer;
    BindBufferFunction BindBuffer;
    BufferDataFunction BufferData;
    BufferSubDataFunction BufferSubData;

    EnableVertexAttribArrayFunction EnableVertexAttribArray;
    VertexAttribPointerFunction VertexAttribPointer;

    CreateProgramFunction CreateProgram;
    DeleteProgramFunction DeleteProgram;
    LinkProgramFunction LinkProgram;
    UseProgramFunction UseProgram;

    CreateShaderFunction CreateShader;
    DeleteShaderFunction DeleteShader;
    AttachShaderFunction AttachShader;
    CompileShaderFunction CompileShader;
    ShaderSourceFunction ShaderSource;

    DrawElementsFunction DrawElements;

    Platform::Module Handle;

    bool Load()
    {
        Handle = Platform::LoadModule(OPENGL_PATH);
        if (!Handle)
            return false;

        Clear = Platform::LoadFunction<ClearFunction>(Handle, "glClear");
        ClearColor = Platform::LoadFunction<ClearColorFunction>(Handle, "glClearColor");

        CreateVertexArray = Platform::LoadFunction<CreateVertexArrayFunction>(Handle, "glGenVertexArrays");
        DeleteVertexArray = Platform::LoadFunction<DeleteVertexArrayFunction>(Handle, "glDeleteVertexArrays");
        BindVertexArray = Platform::LoadFunction<BindVertexArrayFunction>(Handle, "glBindVertexArray");
        
        CreateBuffer = Platform::LoadFunction<CreateBufferFunction>(Handle, "glGenBuffers");
        DeleteBuffer = Platform::LoadFunction<DeleteBufferFunction>(Handle, "glDeleteBuffers");
        BindBuffer = Platform::LoadFunction<BindBufferFunction>(Handle, "glBindBuffer");
        BufferData = Platform::LoadFunction<BufferDataFunction>(Handle, "glBufferData");
        BufferSubData = Platform::LoadFunction<BufferSubDataFunction>(Handle, "glBufferSubData");

        EnableVertexAttribArray = Platform::LoadFunction<EnableVertexAttribArrayFunction>(Handle, "glEnableVertexAttribArray");
        VertexAttribPointer = Platform::LoadFunction<VertexAttribPointerFunction>(Handle, "glVertexAttribPointer");

        CreateProgram = Platform::LoadFunction<CreateProgramFunction>(Handle, "glCreateProgram");
        DeleteProgram = Platform::LoadFunction<DeleteProgramFunction>(Handle, "glDeleteProgram");
        LinkProgram = Platform::LoadFunction<LinkProgramFunction>(Handle, "glLinkProgram");
        UseProgram = Platform::LoadFunction<UseProgramFunction>(Handle, "glUseProgram");

        CreateShader = Platform::LoadFunction<CreateShaderFunction>(Handle, "glCreateShader");
        DeleteShader = Platform::LoadFunction<DeleteShaderFunction>(Handle, "glDeleteShader");
        AttachShader = Platform::LoadFunction<AttachShaderFunction>(Handle, "glAttachShader");
        CompileShader = Platform::LoadFunction<CompileShaderFunction>(Handle, "glCompileShader");
        ShaderSource = Platform::LoadFunction<ShaderSourceFunction>(Handle, "glShaderSource");

        DrawElements = Platform::LoadFunction<DrawElementsFunction>(Handle, "glDrawElements");

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