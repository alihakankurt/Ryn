#pragma once

#include <Ryn/IO/Log.hpp>

#include <vulkan/vulkan_core.h>

namespace Ryn
{
    struct VulkanContext
    {
        VkInstance Instance;
#if RYN_DEBUG
        VkDebugUtilsMessengerEXT DebugMessenger;
#endif
        VkSurfaceKHR Surface;

        static void CheckResult(VkResult result, const char* message);

#if RYN_DEBUG
        static VkBool32 DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );
#endif
    };
}
