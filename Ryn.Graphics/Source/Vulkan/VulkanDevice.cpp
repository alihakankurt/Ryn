#include "VulkanDevice.hpp"

namespace Ryn
{
    VulkanDevice::VulkanDevice(const VulkanInstance& instance) :
        _physicalDevice(VK_NULL_HANDLE),
        _logicalDevice(VK_NULL_HANDLE)
    {
        PickPhysicalDevice(instance);
        CreateLogicalDevice(instance);
    }

    VulkanDevice::~VulkanDevice()
    {
        if (_logicalDevice != VK_NULL_HANDLE)
        {
            vkDeviceWaitIdle(_logicalDevice);
            vkDestroyDevice(_logicalDevice, {});
        }

        _logicalDevice = VK_NULL_HANDLE;
        _physicalDevice = VK_NULL_HANDLE;
    }

    void VulkanDevice::PickPhysicalDevice(const VulkanInstance& instance)
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance.GetInstance(), &deviceCount, {});
        if (deviceCount == 0)
        {
            VK::Error("Failed to find GPUs with Vulkan support!");
        }

        List<VkPhysicalDevice> physicalDevices{deviceCount};
        vkEnumeratePhysicalDevices(instance.GetInstance(), &deviceCount, &physicalDevices.First());

        u64 maxDeviceScore = 0;
        for (const VkPhysicalDevice& physicalDevice : physicalDevices)
        {
            u64 currentDeviceScore = VulkanDevice::CalculatePhysicalDeviceScore(physicalDevice, instance.GetSurface());
            if (currentDeviceScore > maxDeviceScore)
            {
                _physicalDevice = physicalDevice;
                maxDeviceScore = currentDeviceScore;
            }
        }

        if (maxDeviceScore == 0)
        {
            VK::Error("Failed to pick a suitable GPU for Vulkan features!");
        }
    }

    void VulkanDevice::CreateLogicalDevice(const VulkanInstance& instance)
    {
        List<VkDeviceQueueCreateInfo> queueCreateInfos;

        _queueFamilyIndices = VulkanDevice::FindQueueFamilies(_physicalDevice, instance.GetSurface());
        Array<uint32_t, 4> queueFamilyIndicesArray = _queueFamilyIndices.AsArray();
        f32 queuePriority = 1.0f;

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

        List<const char*> deviceExtensions;
        deviceExtensions.Reserve(RequiredDeviceExtensions.Count() + 1);
        for (const char* extension : RequiredDeviceExtensions)
        {
            deviceExtensions.Add(extension);
        }

        if (VulkanDevice::IsPhysicalDeviceHasPortabilitySubsetExtension(_physicalDevice))
        {
            deviceExtensions.Add(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
        }

        VkDeviceCreateInfo logicalDeviceCreateInfo{};
        logicalDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        logicalDeviceCreateInfo.pQueueCreateInfos = &queueCreateInfos.First();
        logicalDeviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.Count());
        logicalDeviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;
        logicalDeviceCreateInfo.ppEnabledExtensionNames = &deviceExtensions.First();
        logicalDeviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.Count());

        VkResult vkResult = vkCreateDevice(_physicalDevice, &logicalDeviceCreateInfo, {}, &_logicalDevice);
        VK::Check(vkResult, "Failed to create logical device for Vulkan features!");
    }

    VulkanDevice::QueueFamilyIndices VulkanDevice::FindQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyPropertyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, {});

        List<VkQueueFamilyProperties> queueFamilyProperties{queueFamilyPropertyCount};
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, &queueFamilyProperties.First());

        for (uint32_t queueFamilyIndex = 0; queueFamilyIndex < queueFamilyPropertyCount; queueFamilyIndex += 1)
        {
            if (queueFamilyProperties[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.GraphicsFamily = queueFamilyIndex;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, &presentSupport);
            if (presentSupport)
            {
                indices.PresentFamily = queueFamilyIndex;
            }

            if (queueFamilyProperties[queueFamilyIndex].queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                indices.TransferFamily = queueFamilyIndex;
            }

            if (queueFamilyProperties[queueFamilyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                indices.ComputeFamily = queueFamilyIndex;
            }

            if (indices.IsSuitable())
            {
                break;
            }
        }

        return indices;
    }

    u64 VulkanDevice::CalculatePhysicalDeviceScore(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        if (!IsPhysicalDeviceExtensionsSupported(physicalDevice))
            return 0;

        uint32_t surfaceFormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, {});
        if (surfaceFormatCount == 0)
            return 0;

        uint32_t presentModeCount = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, {});
        if (presentModeCount == 0)
            return 0;

        QueueFamilyIndices queueFamilyIndices = VulkanDevice::FindQueueFamilies(physicalDevice, surface);
        if (!queueFamilyIndices.IsSuitable())
            return 0;

        u64 deviceScore = 0;

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

    bool VulkanDevice::IsPhysicalDeviceExtensionsSupported(VkPhysicalDevice device)
    {
        uint32_t deviceExtensionCount = 0;
        vkEnumerateDeviceExtensionProperties(device, {}, &deviceExtensionCount, {});
        if (deviceExtensionCount == 0)
            return false;

        List<VkExtensionProperties> deviceExtensions{deviceExtensionCount};
        vkEnumerateDeviceExtensionProperties(device, {}, &deviceExtensionCount, &deviceExtensions.First());

        bool allSupported = RequiredDeviceExtensions.IfAll([deviceExtensions](const char* extension) {
            usz length = String::Length(extension);
            return deviceExtensions.IfAny([extension, length](const VkExtensionProperties& availableExtension) {
                return Memory::Compare(extension, availableExtension.extensionName, length);
            });
        });

        return allSupported;
    }

    bool VulkanDevice::IsPhysicalDeviceHasPortabilitySubsetExtension(VkPhysicalDevice device)
    {
        uint32_t deviceExtensionCount = 0;
        vkEnumerateDeviceExtensionProperties(device, {}, &deviceExtensionCount, {});

        List<VkExtensionProperties> deviceExtensions{deviceExtensionCount};
        vkEnumerateDeviceExtensionProperties(device, {}, &deviceExtensionCount, &deviceExtensions.First());

        bool hasPortabilityExtension = deviceExtensions.IfAny([](const VkExtensionProperties& availableExtension) {
            return Memory::Compare(availableExtension.extensionName, VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME, 25);
        });

        return hasPortabilityExtension;
    }
}
