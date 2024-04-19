#ifndef __RYN_GRAPHICS_OPENGL_OPENGL_RENDERER_HPP__
#define __RYN_GRAPHICS_OPENGL_OPENGL_RENDERER_HPP__

#include <Ryn/Graphics/Renderer.hpp>

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