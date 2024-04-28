#ifndef __RYN_GRAPHICS_OPENGL_SHADER_HPP__
#define __RYN_GRAPHICS_OPENGL_SHADER_HPP__

#include <Ryn/Graphics/Shader.hpp>

namespace Ryn
{
    class OpenGLShader : public Shader
    {
      private:
        u32 _rendererId;

      public:
        OpenGLShader(const string& vertexSource, const string& fragmentSource);
        virtual ~OpenGLShader() override;

        u32 GetRendererId() const;

        virtual void Bind() const override;
        virtual void Unbind() const override;
    };
}

#endif