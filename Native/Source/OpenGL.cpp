#include <Ryn/Native/OpenGL.hpp>

#if RYN_PLATFORM_WINDOWS
#define OPENGL_PATH "opengl32.dll"
#elif RYN_PLATFORM_LINUX
#define OPENGL_PATH "libGL.so"
#elif RYN_PLATFORM_MACOS
#define OPENGL_PATH "/System/Library/Frameworks/OpenGL.framework/OpenGL"
#endif

namespace Ryn
{
    OpenGL::ClearFunction OpenGL::Clear;
    OpenGL::ClearColorFunction OpenGL::ClearColor;

    OpenGL::CreateVertexArrayFunction OpenGL::CreateVertexArray;
    OpenGL::DeleteVertexArrayFunction OpenGL::DeleteVertexArray;
    OpenGL::BindVertexArrayFunction OpenGL::BindVertexArray;

    OpenGL::CreateBufferFunction OpenGL::CreateBuffer;
    OpenGL::DeleteBufferFunction OpenGL::DeleteBuffer;
    OpenGL::BindBufferFunction OpenGL::BindBuffer;
    OpenGL::BufferDataFunction OpenGL::BufferData;
    OpenGL::BufferSubDataFunction OpenGL::BufferSubData;

    OpenGL::EnableVertexAttribArrayFunction OpenGL::EnableVertexAttribArray;
    OpenGL::VertexAttribPointerFunction OpenGL::VertexAttribPointer;

    OpenGL::CreateProgramFunction OpenGL::CreateProgram;
    OpenGL::DeleteProgramFunction OpenGL::DeleteProgram;
    OpenGL::LinkProgramFunction OpenGL::LinkProgram;
    OpenGL::UseProgramFunction OpenGL::UseProgram;

    OpenGL::CreateShaderFunction OpenGL::CreateShader;
    OpenGL::DeleteShaderFunction OpenGL::DeleteShader;
    OpenGL::AttachShaderFunction OpenGL::AttachShader;
    OpenGL::CompileShaderFunction OpenGL::CompileShader;
    OpenGL::ShaderSourceFunction OpenGL::ShaderSource;

    OpenGL::DrawElementsFunction OpenGL::DrawElements;

    Platform::Module OpenGL::Handle;

    bool OpenGL::Load()
    {
        if (Handle)
            return true;

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

    void OpenGL::Unload()
    {
        if (!Handle)
            return;

        Platform::FreeModule(Handle);
        Handle = nullptr;
    }
}
