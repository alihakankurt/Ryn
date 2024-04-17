#ifndef RYN_RENDERING_OPENGL_OPENGL_RENDERER
#define RYN_RENDERING_OPENGL_OPENGL_RENDERER

#include <Ryn/Rendering/Renderer.hpp>

namespace Ryn
{
    class OpenGLRenderer : public Renderer
    {
      public:
        virtual void Clear() override;
        virtual void SetClearColor(const Color& color) override;
    };
}

#endif