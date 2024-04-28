#include <Ryn/Graphics/Shader.hpp>

#include "OpenGL/OpenGLShader.hpp"

namespace Ryn
{
    Ref<Shader> Shader::Create(const string& vertexSource, const string& fragmentSource)
    {
        return Ref<Shader>(new OpenGLShader(vertexSource, fragmentSource));
    }
}
