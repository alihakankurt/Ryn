#include "VulkanDevice.hpp"

namespace Ryn
{
    VulkanDevice::QueueFamilyIndices VulkanDevice::QueueFamilyIndices::Find(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyPropertyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, {});

        List<VkQueueFamilyProperties> queueFamilyPropertiesList{queueFamilyPropertyCount};
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, queueFamilyPropertiesList.Data());

        for (uint32_t queueFamilyIndex = 0; queueFamilyIndex < queueFamilyPropertyCount; queueFamilyIndex += 1)
        {
            if (queueFamilyPropertiesList[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.GraphicsFamily = queueFamilyIndex;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, &presentSupport);
            if (presentSupport)
            {
                indices.PresentFamily = queueFamilyIndex;
            }

            if (queueFamilyPropertiesList[queueFamilyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                indices.ComputeFamily = queueFamilyIndex;
            }

            if (queueFamilyPropertiesList[queueFamilyIndex].queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                indices.TransferFamily = queueFamilyIndex;
            }

            if (indices.IsFound())
            {
                break;
            }
        }

        return indices;
    }

    void VulkanDevice::PickPhysicalDevice(const VulkanInstance& instance, bool& hasPortabilityExtension)
    {
        uint32_t physicalDeviceCount;
        vkEnumeratePhysicalDevices(instance.GetVkInstance(), &physicalDeviceCount, {});
        if (physicalDeviceCount == 0)
        {
            VulkanError("Failed to find GPUs with Vulkan support!");
        }

        List<VkPhysicalDevice> physicalDevices{physicalDeviceCount};
        vkEnumeratePhysicalDevices(instance.GetVkInstance(), &physicalDeviceCount, physicalDevices.Data());

        uint64_t maxScore = 0;
        for (const VkPhysicalDevice& physicalDevice : physicalDevices)
        {
            bool currentHasPortability = false;
            if (!VulkanDevice::IsDeviceExtensionsSupported(physicalDevice, currentHasPortability))
                continue;

            QueueFamilyIndices queueFamilyIndices = QueueFamilyIndices::Find(instance.GetVkSurface(), physicalDevice);
            if (!queueFamilyIndices.IsFound())
                continue;

            uint64_t score = VulkanDevice::CalculateDeviceScore(physicalDevice, instance.GetVkSurface());
            if (score < maxScore)
                continue;

            maxScore = score;
            _physicalDevice = physicalDevice;
            _queueFamilyIndices = queueFamilyIndices;
            hasPortabilityExtension = currentHasPortability;
        }

        if (!_physicalDevice)
        {
            VulkanError("Failed to pick a suitable GPU for Vulkan features!");
        }
    }

    void VulkanDevice::CreateLogicalDevice(bool enablePortabilityExtension)
    {
        List<VkDeviceQueueCreateInfo> queueCreateInfos;
        Array<uint32_t, 4> queueFamilyIndicesArray = _queueFamilyIndices.AsArray();
        float queuePriority = 1.0f;

        for (uint32_t queueFamilyIndex : queueFamilyIndicesArray)
        {
            bool queueAlreadyAdded = queueCreateInfos.IfAny([queueFamilyIndex](const VkDeviceQueueCreateInfo& queueCreateInfo) {
                return queueCreateInfo.queueFamilyIndex == queueFamilyIndex;
            });

            if (queueAlreadyAdded)
                continue;

            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;

            queueCreateInfos.Add(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures physicalDeviceFeatures;
        vkGetPhysicalDeviceFeatures(_physicalDevice, &physicalDeviceFeatures);

        List<const char*> extensionNames;
        extensionNames.Reserve(DeviceExtensionNames.Count + 1);
        for (const char* extensionName : DeviceExtensionNames)
        {
            extensionNames.Add(extensionName);
        }

        if (enablePortabilityExtension)
        {
            extensionNames.Add(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
        }

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.Count());
        createInfo.pQueueCreateInfos = queueCreateInfos.Data();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensionNames.Count());
        createInfo.ppEnabledExtensionNames = extensionNames.Data();
        createInfo.pEnabledFeatures = &physicalDeviceFeatures;

        VkResult result = vkCreateDevice(_physicalDevice, &createInfo, {}, &_logicalDevice);
        VulkanCheck(result, "Failed to create logical device for Vulkan features!");
    }

    void VulkanDevice::DestroyLogicalDevice()
    {
        if (_logicalDevice)
        {
            vkDeviceWaitIdle(_logicalDevice);
            vkDestroyDevice(_logicalDevice, {});
            _logicalDevice = {};
        }
    }

    void VulkanDevice::WaitIdle() const
    {
        vkDeviceWaitIdle(_logicalDevice);
    }

    bool VulkanDevice::IsDeviceExtensionsSupported(VkPhysicalDevice device, bool& hasPortabilityExtension)
    {
        uint32_t extensionPropertiesCount = 0;
        vkEnumerateDeviceExtensionProperties(device, {}, &extensionPropertiesCount, {});
        if (extensionPropertiesCount == 0)
            return false;

        List<VkExtensionProperties> extensionPropertiesList{extensionPropertiesCount};
        vkEnumerateDeviceExtensionProperties(device, {}, &extensionPropertiesCount, extensionPropertiesList.Data());

        bool allSupported = DeviceExtensionNames.IfAll([extensionPropertiesList](const char* extensionName) {
            usz length = String::Length(extensionName);
            return extensionPropertiesList.IfAny([extensionName, length](const VkExtensionProperties& extensionProperties) {
                return Memory::Compare(extensionName, extensionProperties.extensionName, length) == 0;
            });
        });

        hasPortabilityExtension = extensionPropertiesList.IfAny([](const VkExtensionProperties& availableExtension) {
            return Memory::Compare(availableExtension.extensionName, VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME, sizeof(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME)) == 0;
        });

        return allSupported;
    }

    uint64_t VulkanDevice::CalculateDeviceScore(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        uint32_t surfaceFormatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, {});
        if (surfaceFormatCount == 0)
            return 0;

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, {});
        if (presentModeCount == 0)
            return 0;

        uint64_t deviceScore = 0;

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            deviceScore += 1'000;

        if (deviceFeatures.geometryShader)
            deviceScore += 100;

        deviceScore += deviceProperties.limits.maxImageDimension2D;

        return deviceScore;
    }
}
