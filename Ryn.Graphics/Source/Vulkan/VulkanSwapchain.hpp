#pragma once

#include "Vulkan.hpp"
#include "VulkanInstance.hpp"
#include "VulkanDevice.hpp"

namespace Ryn
{
    class VulkanSwapchain
    {
      public:
        struct SupportDetails
        {
            VkSurfaceCapabilitiesKHR Capabilities;
            List<VkSurfaceFormatKHR> Formats;
            List<VkPresentModeKHR> PresentModes;

            VkExtent2D PickExtent2D(const Vector2<u32>& framebufferSize) const;
            VkSurfaceFormatKHR PickSurfaceFormat() const;
            VkPresentModeKHR PickPresentMode() const;
            uint32_t PickImageCount() const;
        };

      private:
        const VulkanDevice& _device;
        VkSwapchainKHR _swapchain;
        VkExtent2D _extent;
        VkSurfaceFormatKHR _surfaceFormat;
        VkPresentModeKHR _presentMode;
        uint32_t _imageCount;

      public:
        VulkanSwapchain(const Window& window, const VulkanInstance& instance, const VulkanDevice& device);
        ~VulkanSwapchain();

        void Recreate(const Window& window, const VulkanInstance& instance);

      private:
        void CreateSwapchain(const Window& window, const VulkanInstance& instance);
        void DestroySwapchain();

        VkSwapchainKHR GetSwapchain() const { return _swapchain; }
        VkExtent2D GetExtent() const { return _extent; }
        VkSurfaceFormatKHR GetSurfaceFormat() const { return _surfaceFormat; }
        VkPresentModeKHR GetPresentMode() const { return _presentMode; }
        uint32_t GetImageCount() const { return _imageCount; }

      public:
        static SupportDetails QuerySupportDetails(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice);
    };
}
