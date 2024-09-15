#include "VulkanRenderer.hpp"

namespace Ryn
{
    VulkanRenderer::VulkanRenderer(const Window& window)
    {
        _instance.Create();
        _surface.Create(_instance, window);
    }

    VulkanRenderer::~VulkanRenderer()
    {
        _surface.Destroy(_instance);
        _instance.Destroy();
    }

    Renderer* Renderer::Create(const Window& window)
    {
        return new VulkanRenderer(window);
    }
}
