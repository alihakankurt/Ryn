#include "../VulkanInstance.hpp"

#include <vulkan/vulkan_metal.h>

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>

namespace Ryn
{
    void VulkanInstance::AddExtensions(List<const char*>& extensions, VkInstanceCreateFlags& createFlags)
    {
        extensions.Add(VK_KHR_SURFACE_EXTENSION_NAME);
        extensions.Add(VK_EXT_METAL_SURFACE_EXTENSION_NAME);
        extensions.Add(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        createFlags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }

    void VulkanInstance::CreateSurface(const Window& window)
    {
        NSWindow* nsWindow = static_cast<NSWindow*>(window.GetNativeHandle());
        NSView* nsView = [nsWindow contentView];
        CAMetalLayer* metalLayer = static_cast<CAMetalLayer*>([nsView layer]);

        VkMetalSurfaceCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
        createInfo.pLayer = metalLayer;

        VkResult result = vkCreateMetalSurfaceEXT(_instance, &createInfo, {}, &_surface);
        VulkanCheck(result, "Failed to create Metal surface");
    }
}
