#include "VulkanRenderer.hpp"

namespace Ryn
{
    Renderer* Renderer::Create(const Window& window)
    {
        return new VulkanRenderer(window);
    }
}
