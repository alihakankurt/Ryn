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
            static constexpr uint32_t NullFamily = static_cast<uint32_t>(-1);

            uint32_t GraphicsFamily = NullFamily;
            uint32_t PresentFamily = NullFamily;
            uint32_t ComputeFamily = NullFamily;
            uint32_t TransferFamily = NullFamily;

            bool IsFound() const
            {
                return GraphicsFamily != NullFamily && PresentFamily != NullFamily
                    && ComputeFamily != NullFamily && TransferFamily != NullFamily;
            }

            Array<uint32_t, 4> AsArray() const
            {
                return {{GraphicsFamily, PresentFamily, ComputeFamily, TransferFamily}};
            }

            static QueueFamilyIndices Find(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice);
        };

      private:
        static constexpr Array<const char*, 1> DeviceExtensionNames = {{
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        }};

      private:
        VkPhysicalDevice _physicalDevice;
        VkDevice _logicalDevice;
        QueueFamilyIndices _queueFamilyIndices;

      public:
        VulkanDevice(const VulkanInstance& instance) :
            _physicalDevice{},
            _logicalDevice{},
            _queueFamilyIndices{} { Create(instance); }

        ~VulkanDevice() { Destroy(); }

        VulkanDevice(const VulkanDevice&) = delete;
        VulkanDevice& operator=(const VulkanDevice&) = delete;

        VulkanDevice(VulkanDevice&& other) :
            _physicalDevice(Utility::Exchange(other._physicalDevice)),
            _logicalDevice(Utility::Exchange(other._logicalDevice)),
            _queueFamilyIndices(Utility::Exchange(other._queueFamilyIndices)) {}

        VulkanDevice& operator=(VulkanDevice&& other)
        {
            if (this != &other)
            {
                Destroy();
                _physicalDevice = Utility::Exchange(other._physicalDevice);
                _logicalDevice = Utility::Exchange(other._logicalDevice);
                _queueFamilyIndices = Utility::Exchange(other._queueFamilyIndices);
            }
            return *this;
        }

        VkPhysicalDevice GetVkPhysicalDevice() const { return _physicalDevice; }
        VkDevice GetVkDevice() const { return _logicalDevice; }
        const QueueFamilyIndices& GetQueueFamilyIndices() const { return _queueFamilyIndices; }

        void Recreate(const VulkanInstance& instance)
        {
            Destroy();
            Create(instance);
        }

        void WaitIdle() const;

      private:
        void Create(const VulkanInstance& instance)
        {
            bool hasPortabilityExtension = false;
            PickPhysicalDevice(instance, hasPortabilityExtension);
            CreateLogicalDevice(hasPortabilityExtension);
        }

        void Destroy()
        {
            DestroyLogicalDevice();
            _physicalDevice = {};
        }

        void PickPhysicalDevice(const VulkanInstance& instance, bool& hasPortabilityExtension);

        void CreateLogicalDevice(bool enablePortabilityExtension);
        void DestroyLogicalDevice();

      private:
        static bool IsDeviceExtensionsSupported(VkPhysicalDevice physicalDevice, bool& hasPortabilityExtension);
        static uint64_t CalculateDeviceScore(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    };
}
