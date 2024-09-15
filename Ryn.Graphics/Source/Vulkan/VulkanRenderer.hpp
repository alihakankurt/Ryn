#pragma once

#include <Ryn/Graphics/Renderer.hpp>

#include "VulkanContext.hpp"

namespace Ryn
{
    class VulkanRenderer : public Renderer
    {
      public:
        VulkanRenderer(const Window& window);

        virtual ~VulkanRenderer() override;

      private:
        VulkanContext _context;
    };
}
