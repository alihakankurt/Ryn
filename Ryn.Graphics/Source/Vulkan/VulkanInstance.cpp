#include "VulkanInstance.hpp"

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Memory.hpp>
#include <Ryn/Core/String.hpp>

namespace Ryn
{
    void VulkanInstance::Create(VulkanContext& context, const Window& window)
    {
        VkApplicationInfo applicationInfo{};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName = "Ryn";
        applicationInfo.applicationVersion = VK_MAKE_VERSION(RYN_VERSION_MAJOR, RYN_VERSION_MINOR, RYN_VERSION_PATCH);
        applicationInfo.pEngineName = "Ryn";
        applicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 1);
        applicationInfo.apiVersion = VK_API_VERSION_1_3;

        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;

        List<const char*> instanceExtensions;
        instanceExtensions.Add(VK_KHR_SURFACE_EXTENSION_NAME);
        AddInstanceExtensions(instanceExtensions, instanceCreateInfo.flags);

#if RYN_DEBUG
        if (CheckValidationLayerSupport())
        {
            Log::Info("Vulkan Validation Layers Supported");
            instanceExtensions.Add(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            instanceCreateInfo.enabledLayerCount = ValidationLayers.Count();
            instanceCreateInfo.ppEnabledLayerNames = &ValidationLayers[0];
        }
        else
        {
            Log::Warn("Vulkan Validation Layers Not Supported");
        }
#endif

        Log::Info("Vulkan Instance Extensions: ", instanceExtensions.Count());
        for (const char* extension : instanceExtensions)
        {
            Log::Info("- ", extension);
        }

        instanceCreateInfo.enabledExtensionCount = instanceExtensions.Count();
        instanceCreateInfo.ppEnabledExtensionNames = &instanceExtensions[0];

        VulkanContext::CheckResult(vkCreateInstance(&instanceCreateInfo, {}, &context.Instance), "Failed to create Vulkan instance");

        Log::Info("Vulkan Instance Created");

#if RYN_DEBUG
        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .pNext = {},
            .flags = {},
            .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
            .pfnUserCallback = VulkanContext::DebugCallback,
            .pUserData = {},
        };

        PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(context.Instance, "vkCreateDebugUtilsMessengerEXT")
        );

        VulkanContext::CheckResult(
            vkCreateDebugUtilsMessengerEXT(context.Instance, &debugMessengerCreateInfo, {}, &context.DebugMessenger),
            "Failed to create Vulkan debug messenger"
        );

        Log::Info("Vulkan Debug Messenger Created");
#endif

        CreateSurface(window, context.Instance, context.Surface);

        Log::Info("Vulkan Surface Created");
    }

    void VulkanInstance::Destroy(VulkanContext& context)
    {
        vkDestroySurfaceKHR(context.Instance, context.Surface, {});
        Log::Info("Vulkan Surface Destroyed");

#if RYN_DEBUG
        PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(context.Instance, "vkDestroyDebugUtilsMessengerEXT")
        );

        vkDestroyDebugUtilsMessengerEXT(context.Instance, context.DebugMessenger, {});
        Log::Info("Vulkan Debug Messenger Destroyed");
#endif

        vkDestroyInstance(context.Instance, {});
        Log::Info("Vulkan Instance Destroyed");
    }

#if RYN_DEBUG
    bool VulkanInstance::CheckValidationLayerSupport()
    {
        u32 layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, {});

        VkLayerProperties availableLayers[layerCount];
        vkEnumerateInstanceLayerProperties(&layerCount, &availableLayers[0]);

        Log::Info("Available Vulkan Validation Layers: ", layerCount);
        for (const VkLayerProperties& layer : availableLayers)
        {
            Log::Info("- ", layer.layerName);
        }

        for (const char* layer : ValidationLayers)
        {
            bool layerFound = false;

            for (const VkLayerProperties& availableLayer : availableLayers)
            {
                u32 length = String::Length(layer);
                if (Memory::Compare(layer, availableLayer.layerName, length) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound)
            {
                return false;
            }
        }

        return true;
    }
#endif
}
