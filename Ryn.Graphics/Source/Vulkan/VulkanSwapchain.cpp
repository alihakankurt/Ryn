#include "VulkanSwapchain.hpp"

namespace Ryn
{
    VulkanSwapchain::VulkanSwapchain(const Window& window, const VulkanInstance& instance, const VulkanDevice& device) :
        _device(device)
    {
        CreateSwapchain(window, instance);
    }

    VulkanSwapchain::~VulkanSwapchain()
    {
        DestroySwapchain();
        _swapchain = VK_NULL_HANDLE;
    }

    void VulkanSwapchain::Recreate(const Window& window, const VulkanInstance& instance)
    {
        DestroySwapchain();
        CreateSwapchain(window, instance);
    }

    void VulkanSwapchain::CreateSwapchain(const Window& window, const VulkanInstance& instance)
    {
        SupportDetails supportDetails = VulkanSwapchain::QuerySupportDetails(instance.GetSurface(), _device.GetPhysicalDevice());

        Vector2<u32> framebufferSize = window.GetFramebufferSize();
        VkExtent2D extent = supportDetails.PickExtent2D(framebufferSize);
        VkSurfaceFormatKHR surfaceFormat = supportDetails.PickSurfaceFormat();
        VkPresentModeKHR presentMode = supportDetails.PickPresentMode();
        uint32_t imageCount = supportDetails.PickImageCount();

        VkSwapchainCreateInfoKHR swapchainCreateInfo{};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.surface = instance.GetSurface();
        swapchainCreateInfo.minImageCount = imageCount;
        swapchainCreateInfo.imageFormat = surfaceFormat.format;
        swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = extent;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        VulkanDevice::QueueFamilyIndices queueFamilyIndices = _device.GetQueueFamilyIndices();
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

        swapchainCreateInfo.preTransform = supportDetails.Capabilities.currentTransform;
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.presentMode = presentMode;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.oldSwapchain = _swapchain;

        VkResult vkResult = vkCreateSwapchainKHR(_device.GetLogicalDevice(), &swapchainCreateInfo, {}, &_swapchain);
        VK::Check(vkResult, "Failed to create Vulkan swapchain!");
    }

    void VulkanSwapchain::DestroySwapchain()
    {
        vkDeviceWaitIdle(_device.GetLogicalDevice());

        if (_swapchain != VK_NULL_HANDLE)
        {
            vkDestroySwapchainKHR(_device.GetLogicalDevice(), _swapchain, {});
        }
    }

    VulkanSwapchain::SupportDetails VulkanSwapchain::QuerySupportDetails(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice)
    {
        VulkanSwapchain::SupportDetails details;

        VkResult vkResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.Capabilities);
        VK::Check(vkResult, "Failed to get Vulkan surface capabilities for physical device!");

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, {});
        if (formatCount != 0)
        {
            details.Formats = List<VkSurfaceFormatKHR>(formatCount);
            vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, &details.Formats.First());
            VK::Check(vkResult, "Failed to get Vulkan surface formats for physical device!");
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, {});
        if (presentModeCount != 0)
        {
            details.PresentModes = List<VkPresentModeKHR>(presentModeCount);
            vkResult = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, &details.PresentModes.First());
            VK::Check(vkResult, "Failed to get Vulkan surface present modes for physical device!");
        }

        return details;
    }

    VkExtent2D VulkanSwapchain::SupportDetails::PickExtent2D(const Vector2<u32>& framebufferSize) const
    {
        if (Capabilities.currentExtent.width != MathConstants<u32>::Max)
        {
            return Capabilities.currentExtent;
        }

        u32 width = Math::Clamp(framebufferSize.X, Capabilities.minImageExtent.width, Capabilities.maxImageExtent.width);
        u32 height = Math::Clamp(framebufferSize.Y, Capabilities.minImageExtent.height, Capabilities.maxImageExtent.height);

        VkExtent2D actualExtent{static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
        return actualExtent;
    }

    VkSurfaceFormatKHR VulkanSwapchain::SupportDetails::PickSurfaceFormat() const
    {
        usz index = Formats.FindFirst([](const VkSurfaceFormatKHR& format) {
            return format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        });

        if (index != Formats.IndexNotFound)
        {
            return Formats[index];
        }

        return Formats.First();
    }

    VkPresentModeKHR VulkanSwapchain::SupportDetails::PickPresentMode() const
    {
        usz index = PresentModes.FindFirst([](const VkPresentModeKHR& presentMode) {
            return presentMode == VK_PRESENT_MODE_MAILBOX_KHR;
        });

        if (index != PresentModes.IndexNotFound)
        {
            return PresentModes[index];
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    uint32_t VulkanSwapchain::SupportDetails::PickImageCount() const
    {
        uint32_t imageCount = Capabilities.minImageCount + 1;
        if (Capabilities.maxImageCount > 0 && imageCount > Capabilities.maxImageCount)
        {
            imageCount = Capabilities.maxImageCount;
        }

        return imageCount;
    }
}
