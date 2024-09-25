#include "VulkanRenderer.hpp"

namespace Ryn
{
    VulkanRenderer::VulkanRenderer(const Window& window)
    {
        _instance.Create(window);
        _device.Create(_instance);
    }

    VulkanRenderer::~VulkanRenderer()
    {
        _device.Destroy();
        _instance.Destroy();
    }

    Renderer* Renderer::Create(const Window& window)
    {
        return new VulkanRenderer(window);
    }
}
