#include "../Vulkan.hpp"

#include <vulkan/vulkan_metal.h>

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>

namespace Ryn::VK
{
    void AddInstanceExtensions(List<const char*>& extensions, VkInstanceCreateFlags& createFlags)
    {
        extensions.Add(VK_KHR_SURFACE_EXTENSION_NAME);
        extensions.Add(VK_EXT_METAL_SURFACE_EXTENSION_NAME);
        extensions.Add(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        createFlags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }

    VkResult CreateSurfaceKHR(const void* window, const VkInstance instance, VkSurfaceKHR* surface)
    {
        NSWindow* nsWindow = static_cast<NSWindow*>(window);
        NSView* nsView = [nsWindow contentView];
        CAMetalLayer* metalLayer = static_cast<CAMetalLayer*>([nsView layer]);

        VkMetalSurfaceCreateInfoEXT surfaceCreateInfo{};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
        surfaceCreateInfo.pLayer = metalLayer;

        return vkCreateMetalSurfaceEXT(instance, &surfaceCreateInfo, {}, surface);
    }
}
