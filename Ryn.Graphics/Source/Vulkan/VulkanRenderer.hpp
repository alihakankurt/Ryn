#pragma once

#include <Ryn/Graphics/Renderer.hpp>

#include "VulkanInstance.hpp"
#include "VulkanDevice.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanRenderPass.hpp"

namespace Ryn
{
    class VulkanRenderer : public Renderer
    {
      private:
        const Window& _window;
        VulkanInstance _instance;
        VulkanDevice _device;
        VulkanSwapchain _swapchain;
        VulkanRenderPass _renderPass;

      public:
        VulkanRenderer(const Window& window) :
            _window{window},
            _instance{_window},
            _device{_instance},
            _swapchain{_window, _instance, _device},
            _renderPass{_device, _swapchain} {}

        virtual ~VulkanRenderer() override {}
    };
}
