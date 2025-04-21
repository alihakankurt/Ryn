#pragma once

#include "Vulkan.hpp"
#include "VulkanDevice.hpp"
#include "VulkanSwapchain.hpp"

namespace Ryn
{
    class VulkanRenderPass
    {
      private:
        const VulkanDevice* _device;
        VkRenderPass _renderPass;

      public:
        VulkanRenderPass(const VulkanDevice& device, const VulkanSwapchain& swapchain) :
            _device{&device},
            _renderPass{} { Create(swapchain); }

        ~VulkanRenderPass() { Destroy(); }

        VulkanRenderPass(const VulkanRenderPass&) = delete;
        VulkanRenderPass& operator=(const VulkanRenderPass&) = delete;

        VulkanRenderPass(VulkanRenderPass&& other) :
            _device{Utility::Exchange(other._device)},
            _renderPass{Utility::Exchange(other._renderPass)} {}

        VulkanRenderPass& operator=(VulkanRenderPass&& other)
        {
            if (this != &other)
            {
                _device = Utility::Exchange(other._device);
                _renderPass = Utility::Exchange(other._renderPass);
            }
            return *this;
        }

        VkRenderPass GetVkRenderPass() const { return _renderPass; }

        void Recreate(const VulkanDevice& device, const VulkanSwapchain& swapchain)
        {
            Destroy();
            _device = &device;
            Create(swapchain);
        }

      private:
        void Create(const VulkanSwapchain& swapchain)
        {
            CreateRenderPass(swapchain);
        }

        void Destroy()
        {
            DestroyRenderPass();
        }

        void CreateRenderPass(const VulkanSwapchain& swapchain);
        void DestroyRenderPass();
    };
}
