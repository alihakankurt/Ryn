#include <Ryn/Native/OpenGL.hpp>

#include "OpenGL/OpenGLRenderer.hpp"

namespace Ryn
{
    void OpenGLRenderer::Clear()
    {
        const u32 mask = 0x00004100;
        OpenGL::Clear(mask);
    }

    void OpenGLRenderer::SetClearColor(const Color& color)
    {
        OpenGL::ClearColor(color.R, color.G, color.B, color.A);
    }
}
