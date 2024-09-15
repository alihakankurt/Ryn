#include "VulkanContext.hpp"

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Process.hpp>

namespace Ryn
{
    void VulkanContext::CheckResult(VkResult result, const char* message)
    {
        if (result != VK_SUCCESS)
        {
            i32 value = static_cast<i32>(result);
            Log::Error(message, " with error code ", value);
            Process::Exit(value);
        }
    }

#if RYN_DEBUG
    VkBool32 VulkanContext::DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    )
    {
        switch (messageSeverity)
        {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                Log::Info("Vulkan: ", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                Log::Warn("Vulkan: ", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            default:
                Log::Error("Vulkan: ", pCallbackData->pMessage);
                break;
        }

        return VK_FALSE;
    }
#endif
}
