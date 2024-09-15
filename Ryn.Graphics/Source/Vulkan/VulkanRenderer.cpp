#include "VulkanRenderer.hpp"
#include "VulkanInstance.hpp"

namespace Ryn
{
    VulkanRenderer::VulkanRenderer(const Window& window)
    {
        VulkanInstance::Create(_context, window);
    }

    VulkanRenderer::~VulkanRenderer()
    {
        VulkanInstance::Destroy(_context);
    }

    Renderer* Renderer::Create(const Window& window)
    {
        return new VulkanRenderer(window);
    }
}
