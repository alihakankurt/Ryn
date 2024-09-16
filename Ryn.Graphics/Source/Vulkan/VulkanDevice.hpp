#pragma once

#include "Vulkan.hpp"
#include "VulkanInstance.hpp"
#include "VulkanSurface.hpp"

namespace Ryn
{
    class VulkanDevice
    {
      public:
        struct QueueFamilyIndices
        {
            static constexpr u32 Invalid = 0xFFFFFFFF;

            u32 GraphicsFamily = Invalid;
            u32 PresentFamily = Invalid;
            u32 TransferFamily = Invalid;
            u32 ComputeFamily = Invalid;

            bool IsSuitable() const
            {
                return GraphicsFamily != Invalid && PresentFamily != Invalid
                    && TransferFamily != Invalid && ComputeFamily != Invalid;
            }

            Array<u32, 4> AsArray() const
            {
                return Array<u32, 4>{{GraphicsFamily, PresentFamily, TransferFamily, ComputeFamily}};
            }
        };

      private:
        static constexpr Array<const char*, 1> DeviceExtensions = {{VK_KHR_SWAPCHAIN_EXTENSION_NAME}};

      private:
        VkPhysicalDevice _physicalDevice;
        VkDevice _logicalDevice;

      public:
        void Create(const VulkanInstance& instance, const VulkanSurface& surface);
        void Destroy();

        VkPhysicalDevice GetPhysical() const { return _physicalDevice; }
        VkDevice GetLogical() const { return _logicalDevice; }

      public:
        static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

      private:
        static u32 CalculateScore(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        static bool IsExtensionsSupported(VkPhysicalDevice physicalDevice);
        static bool HasPortabilitySubsetExtension(VkPhysicalDevice physicalDevice);
    };
}
