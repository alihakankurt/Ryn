#include "VulkanInstance.hpp"

namespace Ryn
{
    void VulkanInstance::Create()
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
        VulkanPlatform::AddInstanceExtensions(instanceExtensions, instanceCreateInfo.flags);

#if RYN_DEBUG
        if (HasValidationLayerSupport())
        {
            instanceExtensions.Add(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            instanceCreateInfo.enabledLayerCount = ValidationLayers.Count();
            instanceCreateInfo.ppEnabledLayerNames = &ValidationLayers[0];
        }
        else
        {
            Log::Warn("Vulkan Validation Layers Not Supported");
        }
#endif

        instanceCreateInfo.enabledExtensionCount = instanceExtensions.Count();
        instanceCreateInfo.ppEnabledExtensionNames = &instanceExtensions[0];

        VK_CHECK_RESULT(vkCreateInstance(&instanceCreateInfo, {}, &_instance), "Failed to create Vulkan instance");

#if RYN_DEBUG
        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{};
        debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
                                                 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                                             | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugMessengerCreateInfo.pfnUserCallback = VulkanDebugCallback;

        PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT")
        );

        VK_CHECK_RESULT(
            vkCreateDebugUtilsMessengerEXT(_instance, &debugMessengerCreateInfo, {}, &_debugMessenger),
            "Failed to create Vulkan debug messenger"
        );
#endif
    }

    void VulkanInstance::Destroy()
    {
#if RYN_DEBUG
        PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT")
        );

        vkDestroyDebugUtilsMessengerEXT(_instance, _debugMessenger, {});
        _debugMessenger = VK_NULL_HANDLE;
#endif

        vkDestroyInstance(_instance, {});
        _instance = VK_NULL_HANDLE;
    }

#if RYN_DEBUG
    bool VulkanInstance::HasValidationLayerSupport()
    {
        u32 layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, {});

        VkLayerProperties* availableLayers = new VkLayerProperties[layerCount];
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);

        bool supported = true;
        for (const char* layer : ValidationLayers)
        {
            bool layerFound = false;
            u32 length = String::Length(layer);

            for (u32 layerIndex = 0; layerIndex < layerCount; ++layerIndex)
            {
                if (Memory::Compare(layer, availableLayers[layerIndex].layerName, length) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound)
            {
                supported = false;
                break;
            }
        }

        delete[] availableLayers;
        return supported;
    }

    VkBool32 VulkanInstance::VulkanDebugCallback(
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
                Log::Info("Vulkan Validation Layer: ", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                Log::Warn("Vulkan Validation Layer: ", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            default:
                Log::Error("Vulkan Validation Layer: ", pCallbackData->pMessage);
                break;
        }

        return VK_FALSE;
    }
#endif
}