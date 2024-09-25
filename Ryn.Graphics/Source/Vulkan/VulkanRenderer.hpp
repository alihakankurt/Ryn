#pragma once

#include <Ryn/Graphics/Renderer.hpp>

#include "VulkanInstance.hpp"
#include "VulkanDevice.hpp"

namespace Ryn
{
    class VulkanRenderer : public Renderer
    {
      private:
        VulkanInstance _instance;
        VulkanDevice _device;

      public:
        VulkanRenderer(const Window& window);

        virtual ~VulkanRenderer() override;
    };
}
