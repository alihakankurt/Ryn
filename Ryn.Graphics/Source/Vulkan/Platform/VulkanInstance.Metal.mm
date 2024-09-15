#include "../VulkanInstance.hpp"

#include <vulkan/vulkan_metal.h>

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>

namespace Ryn
{
    void VulkanInstance::AddInstanceExtensions(List<const char*>& extensions, VkInstanceCreateFlags& flags)
    {
        extensions.Add(VK_EXT_METAL_SURFACE_EXTENSION_NAME);
        extensions.Add(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }

    void VulkanInstance::CreateSurface(const Window& window, VkInstance instance, VkSurfaceKHR& surface)
    {
        NSWindow* nsWindow = static_cast<NSWindow*>(window.GetNativeHandle());
        NSView* nsView = nsWindow.contentView;
        CAMetalLayer* metalLayer = static_cast<CAMetalLayer*>([nsView layer]);

        VkMetalSurfaceCreateInfoEXT createInfo = {
            .sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT,
            .pNext = {},
            .flags = 0,
            .pLayer = metalLayer,
        };

        VulkanContext::CheckResult(vkCreateMetalSurfaceEXT(instance, &createInfo, {}, &surface), "Failed to create Vulkan Metal surface");
    }
}
