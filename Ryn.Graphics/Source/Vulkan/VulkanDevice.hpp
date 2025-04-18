#pragma once

#include "Vulkan.hpp"
#include "VulkanInstance.hpp"

namespace Ryn
{
    class VulkanDevice
    {
      public:
        struct QueueFamilyIndices
        {
            static constexpr uint32_t NullIndex = 0xFFFFFFFF;

            uint32_t GraphicsFamily = NullIndex;
            uint32_t PresentFamily = NullIndex;
            uint32_t TransferFamily = NullIndex;
            uint32_t ComputeFamily = NullIndex;

            bool IsSuitable() const
            {
                return GraphicsFamily != NullIndex && PresentFamily != NullIndex
                    && TransferFamily != NullIndex && ComputeFamily != NullIndex;
            }

            Array<uint32_t, 4> AsArray() const
            {
                return Array<uint32_t, 4>{{GraphicsFamily, PresentFamily, TransferFamily, ComputeFamily}};
            }
        };

      private:
        static constexpr Array<const char*, 1> RequiredDeviceExtensions{{VK_KHR_SWAPCHAIN_EXTENSION_NAME}};

      private:
        VkPhysicalDevice _physicalDevice;
        VkDevice _logicalDevice;
        QueueFamilyIndices _queueFamilyIndices;

      public:
        VulkanDevice(const VulkanInstance& instance);
        ~VulkanDevice();

      private:
        void PickPhysicalDevice(const VulkanInstance& instance);
        void CreateLogicalDevice(const VulkanInstance& instance);

      public:
        VkPhysicalDevice GetPhysicalDevice() const { return _physicalDevice; }
        VkDevice GetLogicalDevice() const { return _logicalDevice; }
        const QueueFamilyIndices& GetQueueFamilyIndices() const { return _queueFamilyIndices; }

      public:
        static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

      private:
        static u64 CalculatePhysicalDeviceScore(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        static bool IsPhysicalDeviceExtensionsSupported(VkPhysicalDevice physicalDevice);
        static bool IsPhysicalDeviceHasPortabilitySubsetExtension(VkPhysicalDevice physicalDevice);
    };
}
