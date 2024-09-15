#include "VulkanSurface.hpp"

namespace Ryn
{
    void VulkanSurface::Create(const VulkanInstance& instance, const Window& window)
    {
        VulkanPlatform::CreateSurface(window, instance.Get(), _surface, {});
        Log::Info("Vulkan Surface Created");
    }

    void VulkanSurface::Destroy(const VulkanInstance& instance)
    {
        vkDestroySurfaceKHR(instance.Get(), _surface, {});
        Log::Info("Vulkan Surface Destroyed");
    }
}
