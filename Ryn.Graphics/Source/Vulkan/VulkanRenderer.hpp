#pragma once

#include <Ryn/Graphics/Renderer.hpp>

#include "VulkanInstance.hpp"
#include "VulkanDevice.hpp"
#include "VulkanSwapchain.hpp"

namespace Ryn
{
    class VulkanRenderer : public Renderer
    {
      private:
        const Window& _window;
        VulkanInstance _instance;
        VulkanDevice _device;
        VulkanSwapchain _swapchain;

      public:
        VulkanRenderer(const Window& window);

        virtual ~VulkanRenderer() override;
    };
}
