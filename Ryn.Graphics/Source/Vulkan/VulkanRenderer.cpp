#include "VulkanRenderer.hpp"

namespace Ryn
{
    Renderer* Renderer::Create(const Window& window)
    {
        return Memory::Allocate<VulkanRenderer>(window);
    }
}
