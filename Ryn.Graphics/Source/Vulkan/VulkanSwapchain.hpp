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
            VkSurfaceCapabilitiesKHR SurfaceCapabilities;
            List<VkSurfaceFormatKHR> SurfaceFormats;
            List<VkPresentModeKHR> PresentModes;

            VkExtent2D PickExtent2D(const Vector2<u32>& framebufferSize) const;
            VkSurfaceFormatKHR PickSurfaceFormat() const;
            VkPresentModeKHR PickPresentMode() const;
            uint32_t PickImageCount() const;

            static SupportDetails Query(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice);
        };

      private:
        const VulkanDevice* _device;
        VkSwapchainKHR _swapchain;
        VkExtent2D _extent;
        VkSurfaceFormatKHR _surfaceFormat;
        VkPresentModeKHR _presentMode;
        uint32_t _imageCount;

      public:
        VulkanSwapchain(const Window& window, const VulkanInstance& instance, const VulkanDevice& device) :
            _device{&device},
            _swapchain{},
            _extent{},
            _surfaceFormat{},
            _presentMode{},
            _imageCount{} { Create(window, instance); }

        ~VulkanSwapchain() { Destroy(); }

        VulkanSwapchain(const VulkanSwapchain&) = delete;
        VulkanSwapchain& operator=(const VulkanSwapchain&) = delete;

        VulkanSwapchain(VulkanSwapchain&& other) :
            _device{Utility::Exchange(other._device)},
            _swapchain{Utility::Exchange(other._swapchain)},
            _extent{Utility::Exchange(other._extent)},
            _surfaceFormat{Utility::Exchange(other._surfaceFormat)},
            _presentMode{Utility::Exchange(other._presentMode)},
            _imageCount{Utility::Exchange(other._imageCount)} {}

        VulkanSwapchain& operator=(VulkanSwapchain&& other)
        {
            if (this != &other)
            {
                Destroy();
                _device = Utility::Exchange(other._device);
                _swapchain = Utility::Exchange(other._swapchain);
                _extent = Utility::Exchange(other._extent);
                _surfaceFormat = Utility::Exchange(other._surfaceFormat);
                _presentMode = Utility::Exchange(other._presentMode);
                _imageCount = Utility::Exchange(other._imageCount);
            }
            return *this;
        }

        VkSwapchainKHR GetVkSwapchain() const { return _swapchain; }
        VkExtent2D GetVkExtent() const { return _extent; }
        VkSurfaceFormatKHR GetVkSurfaceFormat() const { return _surfaceFormat; }
        VkPresentModeKHR GetVkPresentMode() const { return _presentMode; }
        uint32_t GetImageCount() const { return _imageCount; }

        void Recreate(const Window& window, const VulkanInstance& instance, const VulkanDevice& device)
        {
            Destroy();
            _device = &device;
            Create(window, instance);
        }

      private:
        void Create(const Window& window, const VulkanInstance& instance)
        {
            CreateSwapchain(window, instance);
        }

        void Destroy()
        {
            DestroySwapchain();
        }

        void CreateSwapchain(const Window& window, const VulkanInstance& instance);
        void DestroySwapchain();
    };
}
