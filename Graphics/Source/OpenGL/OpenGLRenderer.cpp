#include <Ryn/Native/OpenGL.hpp>

#include "OpenGL/OpenGLRenderer.hpp"

namespace Ryn
{
    void OpenGLRenderer::Clear()
    {
        OpenGL::Clear(OpenGL::ClearMask::Color | OpenGL::ClearMask::Depth);
    }

    void OpenGLRenderer::SetClearColor(const Color& color)
    {
        OpenGL::ClearColor(color.R, color.G, color.B, color.A);
    }
}
