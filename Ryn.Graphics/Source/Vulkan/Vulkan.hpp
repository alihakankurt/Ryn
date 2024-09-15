#pragma once

#include <Ryn/Core/Process.hpp>
#include <Ryn/Collections/List.hpp>
#include <Ryn/IO/Log.hpp>
#include <Ryn/Windowing/Window.hpp>

#include <vulkan/vulkan_core.h>

namespace Ryn
{
    struct VulkanPlatform
    {
        static void AddInstanceExtensions(List<const char*>& extensions, VkInstanceCreateFlags& flags);
        static void CreateSurface(const Window& window, VkInstance instance, VkSurfaceKHR& surface, VkAllocationCallbacks* allocator);

        static void CheckResult(VkResult result, const char* message)
        {
            if (result != VK_SUCCESS)
            {
                i32 value = static_cast<i32>(result);
                Log::Error(message, " with error code ", value);
                Process::Exit(value);
            }
        }
    };
};
