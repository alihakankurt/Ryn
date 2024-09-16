#include "VulkanDevice.hpp"

namespace Ryn
{
    void VulkanDevice::Create(const VulkanInstance& instance, const VulkanSurface& surface)
    {
        u32 deviceCount = 0;
        vkEnumeratePhysicalDevices(instance.Get(), &deviceCount, {});
        if (deviceCount == 0)
        {
            Log::Error("Failed to find GPUs with Vulkan support!");
            Process::Exit(-1);
        }

        VkPhysicalDevice* physicalDevices = new VkPhysicalDevice[deviceCount];
        vkEnumeratePhysicalDevices(instance.Get(), &deviceCount, physicalDevices);

        _physicalDevice = VK_NULL_HANDLE;
        for (u32 deviceIndex = 0, maxDeviceScore = 0; deviceIndex < deviceCount; deviceIndex += 1)
        {
            u32 currentDeviceScore = VulkanDevice::CalculateScore(physicalDevices[deviceIndex], surface.Get());
            if (currentDeviceScore > maxDeviceScore)
            {
                _physicalDevice = physicalDevices[deviceIndex];
                maxDeviceScore = currentDeviceScore;
            }
        }

        delete[] physicalDevices;

        if (_physicalDevice == VK_NULL_HANDLE)
        {
            Log::Error("Failed to find a suitable GPU!");
            Process::Exit(-1);
        }

        List<VkDeviceQueueCreateInfo> queueCreateInfos;

        QueueFamilyIndices queueFamilyIndices = VulkanDevice::FindQueueFamilies(_physicalDevice, surface.Get());
        Array<u32, 4> queueFamilyIndicesArray = queueFamilyIndices.AsArray();
        f32 queuePriority = 1.0f;

        for (u32 queueFamilyIndex : queueFamilyIndicesArray)
        {
            bool queueAlreadyAdded = false;
            for (const VkDeviceQueueCreateInfo& previousQueueCreateInfo : queueCreateInfos)
            {
                if (previousQueueCreateInfo.queueFamilyIndex == queueFamilyIndex)
                {
                    queueAlreadyAdded = true;
                    break;
                }
            }

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
        for (const char* extension : DeviceExtensions)
        {
            deviceExtensions.Add(extension);
        }

        if (VulkanDevice::HasPortabilitySubsetExtension(_physicalDevice))
        {
            deviceExtensions.Add("VK_KHR_portability_subset");
        }

        VkDeviceCreateInfo logicalDeviceCreateInfo{};
        logicalDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        logicalDeviceCreateInfo.pQueueCreateInfos = &queueCreateInfos[0];
        logicalDeviceCreateInfo.queueCreateInfoCount = queueCreateInfos.Count();
        logicalDeviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;
        logicalDeviceCreateInfo.ppEnabledExtensionNames = &deviceExtensions[0];
        logicalDeviceCreateInfo.enabledExtensionCount = deviceExtensions.Count();

        VulkanPlatform::CheckResult(vkCreateDevice(_physicalDevice, &logicalDeviceCreateInfo, {}, &_logicalDevice), "Failed to create Vulkan device");
    }

    void VulkanDevice::Destroy()
    {
        vkDestroyDevice(_logicalDevice, {});
        _physicalDevice = VK_NULL_HANDLE;
        _logicalDevice = VK_NULL_HANDLE;
    }

    VulkanDevice::QueueFamilyIndices VulkanDevice::FindQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        QueueFamilyIndices indices;

        u32 queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, {});

        VkQueueFamilyProperties* queueFamilies = new VkQueueFamilyProperties[queueFamilyCount];
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies);

        for (u32 queueFamilyIndex = 0; queueFamilyIndex < queueFamilyCount; queueFamilyIndex += 1)
        {
            if (queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.GraphicsFamily = queueFamilyIndex;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, &presentSupport);
            if (presentSupport)
            {
                indices.PresentFamily = queueFamilyIndex;
            }

            if (queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                indices.TransferFamily = queueFamilyIndex;
            }

            if (queueFamilies[queueFamilyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                indices.ComputeFamily = queueFamilyIndex;
            }

            if (indices.IsSuitable())
            {
                break;
            }
        }

        delete[] queueFamilies;

        return indices;
    }

    u32 VulkanDevice::CalculateScore(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    {
        if (!IsExtensionsSupported(physicalDevice))
            return 0;

        u32 surfaceFormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, {});
        if (surfaceFormatCount == 0)
            return 0;

        u32 presentModeCount = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, {});
        if (presentModeCount == 0)
            return 0;

        QueueFamilyIndices queueFamilyIndices = VulkanDevice::FindQueueFamilies(physicalDevice, surface);
        if (!queueFamilyIndices.IsSuitable())
            return 0;

        u32 deviceScore = 0;

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

    bool VulkanDevice::IsExtensionsSupported(VkPhysicalDevice device)
    {
        u32 extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(device, {}, &extensionCount, {});

        VkExtensionProperties* availableExtensions = new VkExtensionProperties[extensionCount];
        vkEnumerateDeviceExtensionProperties(device, {}, &extensionCount, availableExtensions);

        bool supported = true;
        for (const char* extension : DeviceExtensions)
        {
            u32 length = String::Length(extension);

            bool extensionFound = false;
            for (u32 extensionIndex = 0; extensionIndex < extensionCount; extensionIndex += 1)
            {
                if (Memory::Compare(availableExtensions[extensionIndex].extensionName, extension, length))
                {
                    extensionFound = true;
                    break;
                }
            }

            if (!extensionFound)
            {
                supported = false;
                break;
            }
        }

        delete[] availableExtensions;
        return supported;
    }

    bool VulkanDevice::HasPortabilitySubsetExtension(VkPhysicalDevice device)
    {
        u32 extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(device, {}, &extensionCount, {});

        VkExtensionProperties* availableExtensions = new VkExtensionProperties[extensionCount];
        vkEnumerateDeviceExtensionProperties(device, {}, &extensionCount, availableExtensions);

        bool hasExtension = false;
        for (u32 extensionIndex = 0; extensionIndex < extensionCount; extensionIndex += 1)
        {
            if (Memory::Compare(availableExtensions[extensionIndex].extensionName, "VK_KHR_portability_subset", 25))
            {
                hasExtension = true;
                break;
            }
        }

        delete[] availableExtensions;
        return hasExtension;
    }
}
