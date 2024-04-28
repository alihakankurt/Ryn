#include <Ryn/Native/OpenGL.hpp>

#include "OpenGL/OpenGLShader.hpp"

namespace Ryn
{
    OpenGLShader::OpenGLShader(const string& vertexSource, const string& fragmentSource)
    {
        u32 vertexShader = OpenGL::CreateShader(OpenGL::ShaderType::Vertex);
        u32 fragmentShader = OpenGL::CreateShader(OpenGL::ShaderType::Fragment);

        auto vertexSourceData = const_cast<char*>(vertexSource.Data());
        auto fragmentSourceData = const_cast<char*>(fragmentSource.Data());

        OpenGL::ShaderSource(vertexShader, 1, &vertexSourceData, nullptr);
        OpenGL::ShaderSource(fragmentShader, 1, &fragmentSourceData, nullptr);

        OpenGL::CompileShader(vertexShader);
        OpenGL::CompileShader(fragmentShader);

        _rendererId = OpenGL::CreateProgram();
        OpenGL::AttachShader(_rendererId, vertexShader);
        OpenGL::AttachShader(_rendererId, fragmentShader);
        OpenGL::LinkProgram(_rendererId);

        OpenGL::DeleteShader(vertexShader);
        OpenGL::DeleteShader(fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        OpenGL::DeleteProgram(_rendererId);
    }

    u32 OpenGLShader::GetRendererId() const
    {
        return _rendererId;
    }

    void OpenGLShader::Bind() const
    {
        OpenGL::UseProgram(_rendererId);
    }

    void OpenGLShader::Unbind() const
    {
        OpenGL::UseProgram(0);
    }
}
