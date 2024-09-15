#pragma once

#include <Ryn/Graphics/Renderer.hpp>

#include "VulkanInstance.hpp"
#include "VulkanSurface.hpp"

namespace Ryn
{
    class VulkanRenderer : public Renderer
    {
      private:
        VulkanInstance _instance;
        VulkanSurface _surface;

      public:
        VulkanRenderer(const Window& window);

        virtual ~VulkanRenderer() override;
    };
}
