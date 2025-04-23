#include "VulkanInstance.hpp"

namespace Ryn
{
    void VulkanInstance::CreateInstance()
    {
        VkApplicationInfo applicationInfo{};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName = "Ryn";
        applicationInfo.applicationVersion = VK_MAKE_VERSION(RYN_VERSION_MAJOR, RYN_VERSION_MINOR, RYN_VERSION_PATCH);
        applicationInfo.pEngineName = "Ryn";
        applicationInfo.engineVersion = VK_MAKE_VERSION(RYN_VERSION_MAJOR, RYN_VERSION_MINOR, RYN_VERSION_PATCH);
        applicationInfo.apiVersion = VK_API_VERSION_1_4;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &applicationInfo;

        List<const char*> extensionNames;
        VkInstanceCreateFlags createFlags = 0;
        VulkanInstance::AddExtensions(extensionNames, createFlags);

#if RYN_DEBUG
        if (!IfValidationLayersSupported())
        {
            VulkanError("Validation layers are not supported!");
        }

        extensionNames.Add(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        createInfo.enabledLayerCount = ValidationLayerNames.Count;
        createInfo.ppEnabledLayerNames = ValidationLayerNames.Data();

        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{};
        PopulateDebugMessengerCreateInfo(debugMessengerCreateInfo);
        createInfo.pNext = &debugMessengerCreateInfo;
#endif

        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNames.Count());
        createInfo.ppEnabledExtensionNames = extensionNames.Data();
        createInfo.flags = createFlags;

        VkResult result = vkCreateInstance(&createInfo, {}, &_instance);
        VulkanCheck(result, "Failed to create a Vulkan instance!");
    }

    void VulkanInstance::DestroyInstance()
    {
        if (_instance)
        {
            vkDestroyInstance(_instance, {});
            _instance = {};
        }
    }

    void VulkanInstance::DestroySurface()
    {
        if (_surface)
        {
            vkDestroySurfaceKHR(_instance, _surface, {});
            _surface = {};
        }
    }

#if RYN_DEBUG
    void VulkanInstance::CreateDebugMessenger()
    {
        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{};
        PopulateDebugMessengerCreateInfo(debugMessengerCreateInfo);

        auto vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT")
        );

        if (vkCreateDebugUtilsMessengerEXT)
        {
            VkResult result = vkCreateDebugUtilsMessengerEXT(_instance, &debugMessengerCreateInfo, {}, &_debugMessenger);
            VulkanCheck(result, "Failed to create a debug messenger!");
        }
    }

    void VulkanInstance::DestroyDebugMessenger()
    {
        if (_debugMessenger)
        {
            auto vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
                vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT")
            );

            if (vkDestroyDebugUtilsMessengerEXT)
            {
                vkDestroyDebugUtilsMessengerEXT(_instance, _debugMessenger, {});
            }

            _debugMessenger = {};
        }
    }

    void VulkanInstance::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo)
    {
        debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                                                 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
                                                 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                                                 | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                                             | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                                             | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugMessengerCreateInfo.pfnUserCallback = OnDebugMessage;
    }

    bool VulkanInstance::IfValidationLayersSupported()
    {
        uint32_t layerPropertiesCount;
        vkEnumerateInstanceLayerProperties(&layerPropertiesCount, {});

        List<VkLayerProperties> layerPropertiesList{layerPropertiesCount};
        vkEnumerateInstanceLayerProperties(&layerPropertiesCount, layerPropertiesList.Data());

        bool allSupported = ValidationLayerNames.IfAll([layerPropertiesList](const char* validationLayerName) {
            usz length = String::Length(validationLayerName);
            return layerPropertiesList.IfAny([validationLayerName, length](const VkLayerProperties& layerProperties) {
                return Memory::Compare(validationLayerName, layerProperties.layerName, length) == 0;
            });
        });

        return allSupported;
    }

    VkBool32 VulkanInstance::OnDebugMessage(
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
                Log::Info("(Vulkan - ", pCallbackData->pMessageIdName, ") ", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                Log::Warn("(Vulkan - ", pCallbackData->pMessageIdName, ") ", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            default:
                Log::Error("(Vulkan - ", pCallbackData->pMessageIdName, ") ", pCallbackData->pMessage);
                break;
        }

        return VK_FALSE;
    }
#endif
}