#include "VulkanRenderer.hpp"

namespace Ryn
{
    VulkanRenderer::VulkanRenderer(const Window& window) :
        _window(window),
        _instance(window),
        _device(_instance),
        _swapchain(window, _instance, _device) {}

    VulkanRenderer::~VulkanRenderer()
    {
    }

    Renderer* Renderer::Create(const Window& window)
    {
        return new VulkanRenderer(window);
    }
}
