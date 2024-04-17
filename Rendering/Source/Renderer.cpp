#include <Ryn/Rendering/Renderer.hpp>

#include "OpenGL/OpenGLRenderer.hpp"

namespace Ryn
{
    Renderer* Renderer::Create()
    {
        return new OpenGLRenderer();
    }
}