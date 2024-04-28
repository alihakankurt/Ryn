#ifndef __RYN_GRAPHICS_OPENGL_RENDERER_HPP__
#define __RYN_GRAPHICS_OPENGL_RENDERER_HPP__

#include <Ryn/Graphics/Renderer.hpp>
#include <Ryn/Graphics/Buffer.hpp>
#include <Ryn/Graphics/Shader.hpp>

namespace Ryn
{
    class OpenGLRenderer : public Renderer
    {
      private:
        static constexpr isize VertexSize = sizeof(f32) * 6;
        static constexpr isize VertexPerQuad = 4;
        static constexpr isize IndexPerQuad = 6;
        static constexpr isize QuadCount = 64;
        static constexpr isize VertexCount = VertexPerQuad * QuadCount;
        static constexpr isize IndexCount = IndexPerQuad * QuadCount;

      private:
        u32 _vao;
        Ref<Buffer> _indexBuffer;
        Ref<Buffer> _vertexBuffer;
        Ref<Shader> _colorShader;
        isize _vertexCount;

      public:
        OpenGLRenderer();
        virtual ~OpenGLRenderer() override;

        virtual void Present() override;

        virtual void Clear() override;
        virtual void SetClearColor(const Color& color) override;

        virtual void BeginFrame() override;
        virtual void EndFrame() override;

        virtual void DrawQuad(const Vector2<f32>& position, const Vector2<f32>& size, const Color& color) override;
    };
}

#endif