#include "../Vulkan.hpp"

#include <vulkan/vulkan_metal.h>

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>

namespace Ryn
{
    void VulkanPlatform::AddInstanceExtensions(List<const char*>& extensions, VkInstanceCreateFlags& flags)
    {
        extensions.Add(VK_EXT_METAL_SURFACE_EXTENSION_NAME);
        extensions.Add(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }

    void VulkanPlatform::CreateSurface(const Window& window, VkInstance instance, VkSurfaceKHR& surface, VkAllocationCallbacks* allocator)
    {
        NSWindow* nsWindow = static_cast<NSWindow*>(window.GetNativeHandle());
        NSView* nsView = [nsWindow contentView];
        CAMetalLayer* metalLayer = static_cast<CAMetalLayer*>([nsView layer]);

        VkMetalSurfaceCreateInfoEXT surfaceCreateInfo{};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
        surfaceCreateInfo.pLayer = metalLayer;

        VulkanPlatform::CheckResult(vkCreateMetalSurfaceEXT(instance, &surfaceCreateInfo, allocator, &surface), "Failed to create Vulkan Metal surface");
    }
}
