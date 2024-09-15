#pragma once

#include <Ryn/Collections/Array.hpp>
#include <Ryn/Collections/List.hpp>
#include <Ryn/Windowing/Window.hpp>

#include "VulkanContext.hpp"

namespace Ryn
{
    class VulkanInstance
    {
      private:
#if RYN_DEBUG
        static constexpr Array<const char*, 1> ValidationLayers = {{
            "VK_LAYER_KHRONOS_validation",
        }};
#endif

      public:
        VulkanInstance() = delete;
        ~VulkanInstance() = delete;

        static void Create(VulkanContext& context, const Window& window);
        static void Destroy(VulkanContext& context);

      private:
        static void AddInstanceExtensions(List<const char*>& extensions, VkInstanceCreateFlags& flags);
        static void CreateSurface(const Window& window, VkInstance instance, VkSurfaceKHR& surface);

#if RYN_DEBUG
        static bool CheckValidationLayerSupport();
#endif
    };
}
