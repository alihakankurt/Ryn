#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Memory.hpp>
#include <Ryn/Core/String.hpp>
#include <Ryn/Core/Process.hpp>
#include <Ryn/Collections/Array.hpp>
#include <Ryn/Collections/List.hpp>
#include <Ryn/IO/Log.hpp>
#include <Ryn/Windowing/Window.hpp>

#include <vulkan/vulkan_core.h>

#if RYN_DEBUG
    #define VK_KHR_VALIDATION_LAYER_EXTENSION_NAME "VK_LAYER_KHRONOS_validation"
#endif

#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"

#define VK_ERROR(...)            \
    do                           \
    {                            \
        Log::Error(__VA_ARGS__); \
        Process::Exit(-1);       \
    }                            \
    while (0)

#define VK_CHECK_RESULT(result, ...) \
    if (result != VK_SUCCESS) VK_ERROR(__VA_ARGS__)

VKAPI_ATTR VkResult VKAPI_CALL vkCreateSurfaceKHR(
    void* window,
    const VkInstance instance,
    VkSurfaceKHR* surface,
    const VkAllocationCallbacks* pAllocator
);

VKAPI_ATTR void VKAPI_CALL vkAddInstanceExtensions(
    Ryn::List<const char*>& extensions,
    VkInstanceCreateFlags& flags
);
