#include <Ryn/Graphics/Renderer.hpp>

#include "OpenGL/OpenGLRenderer.hpp"

namespace Ryn
{
    Ref<Renderer> Renderer::Create()
    {
        return Ref<Renderer>(new OpenGLRenderer());
    }
}