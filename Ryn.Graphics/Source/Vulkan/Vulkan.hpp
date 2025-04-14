#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Memory.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/String.hpp>
#include <Ryn/Core/Process.hpp>
#include <Ryn/Collections/Array.hpp>
#include <Ryn/Collections/List.hpp>
#include <Ryn/IO/Log.hpp>
#include <Ryn/Windowing/Window.hpp>

#include <vulkan/vulkan_core.h>

#define VK_KHR_VALIDATION_LAYER_EXTENSION_NAME "VK_LAYER_KHRONOS_validation"
#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

namespace Ryn::VK
{
    template <typename... TArgs>
    void Error(TArgs&&... args)
    {
        Log::Error("(Vulkan) ", Utility::Forward<TArgs>(args)...);
        Process::Exit(-1);
    }

    template <typename... TArgs>
    void Check(VkResult result, TArgs&&... args)
    {
        if (result != VK_SUCCESS)
        {
            VK::Error(Utility::Forward<TArgs>(args)...);
        }
    }

    void AddInstanceExtensions(List<const char*>& extensions, VkInstanceCreateFlags& createFlags);
    VkResult CreateSurfaceKHR(const Window& window, const VkInstance instance, VkSurfaceKHR* surface);
}
