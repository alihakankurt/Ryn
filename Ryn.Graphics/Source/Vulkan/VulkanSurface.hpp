#pragma once

#include "Vulkan.hpp"
#include "VulkanInstance.hpp"

namespace Ryn
{
    class VulkanSurface
    {
      private:
        VkSurfaceKHR _surface;

      public:
        void Create(const VulkanInstance& instance, const Window& window);
        void Destroy(const VulkanInstance& instance);

        VkSurfaceKHR Get() const { return _surface; }
    };
}