#include "VulkanSwapchain.hpp"

namespace Ryn
{
    VulkanSwapchain::SupportDetails VulkanSwapchain::SupportDetails::Query(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice)
    {
        VulkanSwapchain::SupportDetails details;

        VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.SurfaceCapabilities);
        VulkanCheck(result, "Failed to get Vulkan surface capabilities for physical device!");

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, {});
        if (formatCount != 0)
        {
            details.SurfaceFormats = List<VkSurfaceFormatKHR>(formatCount);
            result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.SurfaceFormats.Data());
            VulkanCheck(result, "Failed to get Vulkan surface formats for physical device!");
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, {});
        if (presentModeCount != 0)
        {
            details.PresentModes = List<VkPresentModeKHR>(presentModeCount);
            result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.PresentModes.Data());
            VulkanCheck(result, "Failed to get Vulkan surface present modes for physical device!");
        }

        return details;
    }

    VkExtent2D VulkanSwapchain::SupportDetails::PickExtent2D(const Vector2<u32>& framebufferSize) const
    {
        if (SurfaceCapabilities.currentExtent.width != MathConstants<u32>::Max)
        {
            return SurfaceCapabilities.currentExtent;
        }

        u32 actualWidth = Math::Clamp(framebufferSize.X, SurfaceCapabilities.minImageExtent.width, SurfaceCapabilities.maxImageExtent.width);
        u32 actualHeight = Math::Clamp(framebufferSize.Y, SurfaceCapabilities.minImageExtent.height, SurfaceCapabilities.maxImageExtent.height);

        VkExtent2D actualExtent{
            static_cast<uint32_t>(actualWidth),
            static_cast<uint32_t>(actualHeight)
        };

        return actualExtent;
    }

    VkSurfaceFormatKHR VulkanSwapchain::SupportDetails::PickSurfaceFormat() const
    {
        auto it = SurfaceFormats.FindFirst([](const VkSurfaceFormatKHR& format) {
            return format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        });

        if (it != SurfaceFormats.End())
        {
            return *it;
        }

        return SurfaceFormats.First();
    }

    VkPresentModeKHR VulkanSwapchain::SupportDetails::PickPresentMode() const
    {
        auto it = PresentModes.FindFirst([](const VkPresentModeKHR& presentMode) {
            return presentMode == VK_PRESENT_MODE_MAILBOX_KHR;
        });

        if (it != PresentModes.End())
        {
            return *it;
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    uint32_t VulkanSwapchain::SupportDetails::PickImageCount() const
    {
        uint32_t imageCount = SurfaceCapabilities.minImageCount + 1;
        if (SurfaceCapabilities.maxImageCount > 0)
        {
            imageCount = Math::Min(imageCount, SurfaceCapabilities.maxImageCount);
        }

        return imageCount;
    }

    uint32_t VulkanSwapchain::AcquireNextImage(uint64_t timeout) const
    {
        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(_device->GetVkDevice(), _swapchain, timeout, {}, {}, &imageIndex);
        VulkanCheck(result, "Failed to acquire next Vulkan swapchain image!");
        return imageIndex;
    }

    void VulkanSwapchain::CreateSwapchain(const Window& window, const VulkanInstance& instance)
    {
        SupportDetails supportDetails = VulkanSwapchain::SupportDetails::Query(instance.GetVkSurface(), _device->GetVkPhysicalDevice());

        Vector2<u32> framebufferSize = window.GetFramebufferSize();
        _extent = supportDetails.PickExtent2D(framebufferSize);
        _surfaceFormat = supportDetails.PickSurfaceFormat();
        _presentMode = supportDetails.PickPresentMode();
        _imageCount = supportDetails.PickImageCount();

        VkSwapchainCreateInfoKHR swapchainCreateInfo{};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.surface = instance.GetVkSurface();
        swapchainCreateInfo.minImageCount = _imageCount;
        swapchainCreateInfo.imageFormat = _surfaceFormat.format;
        swapchainCreateInfo.imageColorSpace = _surfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = _extent;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        VulkanDevice::QueueFamilyIndices queueFamilyIndices = _device->GetQueueFamilyIndices();
        uint32_t graphicsAndPresentIndices[]{queueFamilyIndices.GraphicsFamily, queueFamilyIndices.PresentFamily};

        if (queueFamilyIndices.GraphicsFamily != queueFamilyIndices.PresentFamily)
        {
            swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            swapchainCreateInfo.queueFamilyIndexCount = 2;
            swapchainCreateInfo.pQueueFamilyIndices = graphicsAndPresentIndices;
        }
        else
        {
            swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        swapchainCreateInfo.preTransform = supportDetails.SurfaceCapabilities.currentTransform;
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.presentMode = _presentMode;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.oldSwapchain = _swapchain;

        VkResult result = vkCreateSwapchainKHR(_device->GetVkDevice(), &swapchainCreateInfo, {}, &_swapchain);
        VulkanCheck(result, "Failed to create Vulkan swapchain!");
    }

    void VulkanSwapchain::DestroySwapchain()
    {
        if (_swapchain)
        {
            vkDestroySwapchainKHR(_device->GetVkDevice(), _swapchain, {});
            _swapchain = {};
        }
    }

    void VulkanSwapchain::RetreiveSwapchainImages()
    {
        _swapchainImages = List<VkImage>{_imageCount};

        VkResult result = vkGetSwapchainImagesKHR(_device->GetVkDevice(), _swapchain, &_imageCount, _swapchainImages.Data());
        VulkanCheck(result, "Failed to get Vulkan swapchain images!");
    }

    void VulkanSwapchain::CleanupSwapchainImages()
    {
        _swapchainImages.Clear();
    }

    void VulkanSwapchain::CreateSwapchainImageViews()
    {
        _swapchainImageViews.Reserve(_imageCount);

        for (VkImage swapchainImage : _swapchainImages)
        {
            VkImageViewCreateInfo imageViewCreateInfo{};
            imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            imageViewCreateInfo.image = swapchainImage;
            imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            imageViewCreateInfo.format = _surfaceFormat.format;
            imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
            imageViewCreateInfo.subresourceRange.levelCount = 1;
            imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
            imageViewCreateInfo.subresourceRange.layerCount = 1;

            VkImageView swapchainImageView;
            VkResult result = vkCreateImageView(_device->GetVkDevice(), &imageViewCreateInfo, {}, &swapchainImageView);
            VulkanCheck(result, "Failed to create swap chain image view");

            _swapchainImageViews.Add(swapchainImageView);
        }
    }

    void VulkanSwapchain::DestroySwapchainImageViews()
    {
        for (VkImageView swapchainImageView : _swapchainImageViews)
        {
            vkDestroyImageView(_device->GetVkDevice(), swapchainImageView, {});
        }

        _swapchainImageViews.Clear();
    }
}
