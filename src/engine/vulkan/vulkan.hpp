#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <vector>

namespace Engine {
    class Vulkan {
        public:
            Vulkan();
            ~Vulkan();

            Vulkan(const Vulkan &) = delete;
            Vulkan &operator=(const Vulkan &) = delete;

        private:
            VkInstance instance = nullptr;
            VkDebugUtilsMessengerEXT debugMessenger;

            static constexpr const char* APP_NAME = "Engine";
            static constexpr const char* ENGINE_NAME = "No Engine";
            
            const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

            #ifdef NDEBUG
                const bool enableValidationLayers = false;
            #else
                const bool enableValidationLayers = true;
            #endif

            void init();

            bool checkValidationLayerSupport();

            std::vector<const char*> getRequiredExtensions();

            // Message callback
            void setupDebugMessenger();

            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

            VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

            void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    };
}
