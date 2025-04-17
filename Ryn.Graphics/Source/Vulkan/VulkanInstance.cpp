#include "VulkanInstance.hpp"

namespace Ryn
{
    VulkanInstance::VulkanInstance(const Window& window) :
        _instance(VK_NULL_HANDLE),
#if RYN_DEBUG
        _debugMessenger(VK_NULL_HANDLE),
#endif
        _surface(VK_NULL_HANDLE)
    {
        CreateInstance();
#if RYN_DEBUG
        CreateDebugMessenger();
#endif
        CreateSurface(window);
    }

    VulkanInstance::~VulkanInstance()
    {
        if (_surface != VK_NULL_HANDLE)
        {
            vkDestroySurfaceKHR(_instance, _surface, {});
        }

#if RYN_DEBUG
        if (_debugMessenger != VK_NULL_HANDLE)
        {
            PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
                vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT")
            );

            vkDestroyDebugUtilsMessengerEXT(_instance, _debugMessenger, {});
        }
#endif

        if (_instance != VK_NULL_HANDLE)
        {
            vkDestroyInstance(_instance, {});
        }

        _surface = VK_NULL_HANDLE;
#if RYN_DEBUG
        _debugMessenger = VK_NULL_HANDLE;
#endif
        _instance = VK_NULL_HANDLE;
    }

    void VulkanInstance::CreateInstance()
    {
        VkApplicationInfo applicationInfo{};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName = "Ryn";
        applicationInfo.applicationVersion = VK_MAKE_API_VERSION(0, RYN_VERSION_MAJOR, RYN_VERSION_MINOR, RYN_VERSION_PATCH);
        applicationInfo.pEngineName = "Ryn";
        applicationInfo.engineVersion = VK_MAKE_API_VERSION(0, RYN_VERSION_MAJOR, RYN_VERSION_MINOR, RYN_VERSION_PATCH);
        applicationInfo.apiVersion = VK_API_VERSION_1_4;

        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;

        List<const char*> instanceExtensions;
        VkInstanceCreateFlags instanceCreateFlags = 0;
        VK::AddInstanceExtensions(instanceExtensions, instanceCreateFlags);

#if RYN_DEBUG
        if (IsValidationLayersSupported())
        {
            instanceExtensions.Add(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            instanceCreateInfo.enabledLayerCount = ValidationLayers.Count();
            instanceCreateInfo.ppEnabledLayerNames = ValidationLayers.Data();
        }
        else
        {
            VK::Error("Validation layers are not supported!");
        }
#endif

        instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.Count());
        instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.Data();
        instanceCreateInfo.flags = instanceCreateFlags;

        VkResult vkResult = vkCreateInstance(&instanceCreateInfo, {}, &_instance);
        VK::Check(vkResult, "Failed to create a Vulkan instance!");
    }

#if RYN_DEBUG
    void VulkanInstance::CreateDebugMessenger()
    {
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

        VkResult vkResult = vkCreateDebugUtilsMessengerEXT(_instance, &debugMessengerCreateInfo, {}, &_debugMessenger);
        VK::Check(vkResult, "Failed to create a debug messenger!");
    }
#endif

    void VulkanInstance::CreateSurface(const Window& window)
    {
        VkResult vkResult = VK::CreateSurfaceKHR(window.GetNativeHandle(), _instance, &_surface);
        VK::Check(vkResult, "Failed to create a surface!");
    }

#if RYN_DEBUG
    bool VulkanInstance::IsValidationLayersSupported()
    {
        uint32_t instanceLayerCount;
        vkEnumerateInstanceLayerProperties(&instanceLayerCount, {});

        List<VkLayerProperties> instanceLayers{instanceLayerCount};
        vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayers.Data());

        bool allSupported = ValidationLayers.IfAll([instanceLayers](const char* layer) {
            usz length = String::Length(layer);
            return instanceLayers.IfAny([layer, length](const VkLayerProperties& availableLayer) {
                return Memory::Compare(layer, availableLayer.layerName, length) == 0;
            });
        });

        return allSupported;
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