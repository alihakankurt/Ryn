#pragma once

#include "Vulkan.hpp"

namespace Ryn
{
    class VulkanInstance
    {
      private:
        VkInstance _instance;
#if RYN_DEBUG
        VkDebugUtilsMessengerEXT _debugMessenger;
        static constexpr Array<const char*, 1> ValidationLayers{{VK_KHR_VALIDATION_LAYER_EXTENSION_NAME}};
#endif
        VkSurfaceKHR _surface;

      public:
        void Create(const Window& window);
        void Destroy();

        VkInstance Get() const { return _instance; }
        VkSurfaceKHR GetSurface() const { return _surface; }

      private:
#if RYN_DEBUG
        static bool HasValidationLayerSupport();
        static VkBool32 VulkanDebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );
#endif
    };
}
