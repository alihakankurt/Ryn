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
#endif
        VkSurfaceKHR _surface;

      public:
        VulkanInstance(const Window& window) :
            _instance{},
#if RYN_DEBUG
            _debugMessenger{},
#endif
            _surface{} { Create(window); }

        ~VulkanInstance() { Destroy(); }

        VulkanInstance(const VulkanInstance&) = delete;
        VulkanInstance& operator=(const VulkanInstance&) = delete;

        VulkanInstance(VulkanInstance&& other) :
            _instance{Utility::Exchange(other._instance)},
#if RYN_DEBUG
            _debugMessenger{Utility::Exchange(other._debugMessenger)},
#endif
            _surface{Utility::Exchange(other._surface)} {}

        VulkanInstance& operator=(VulkanInstance&& other)
        {
            if (this != &other)
            {
                Destroy();
                _instance = Utility::Exchange(other._instance);
#if RYN_DEBUG
                _debugMessenger = Utility::Exchange(other._debugMessenger);
#endif
                _surface = Utility::Exchange(other._surface);
            }
            return *this;
        }

        VkInstance GetVkInstance() const { return _instance; }
        VkSurfaceKHR GetVkSurface() const { return _surface; }
        
        void Recreate(const Window& window)
        {
            Destroy();
            Create(window);
        }

      private:
        void Create(const Window& window)
        {
            CreateInstance();
#if RYN_DEBUG
            CreateDebugMessenger();
#endif
            CreateSurface(window);
        }

        void Destroy()
        {
            DestroySurface();
#if RYN_DEBUG
            DestroyDebugMessenger();
#endif
            DestroyInstance();
        }

        void CreateInstance();
        void DestroyInstance();

        void CreateSurface(const Window& window);
        void DestroySurface();

      private:
        static void AddExtensions(List<const char*>& extensions, VkInstanceCreateFlags& createFlags);

#if RYN_DEBUG
        static constexpr Array<const char*, 1> ValidationLayerNames = {{
            VK_KHR_VALIDATION_LAYER_EXTENSION_NAME,
        }};

        void CreateDebugMessenger();
        void DestroyDebugMessenger();

        static bool IfValidationLayersSupported();
        static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugMessengerCreateInfo);

        static VkBool32 OnDebugMessage(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );
#endif
    };
}
