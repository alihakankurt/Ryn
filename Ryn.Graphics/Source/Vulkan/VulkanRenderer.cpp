#include "VulkanRenderer.hpp"

namespace Ryn
{
    VulkanRenderer::VulkanRenderer(const Window& window) :
        _instance(window.GetNativeHandle()),
        _device(_instance) {}

    VulkanRenderer::~VulkanRenderer()
    {
    }

    Renderer* Renderer::Create(const Window& window)
    {
        return new VulkanRenderer(window);
    }
}
