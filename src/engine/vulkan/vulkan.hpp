#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <vector>
#include <iostream>
#include <optional>

namespace Engine {
    class Vulkan {
        public:
            Vulkan();
            ~Vulkan();

            Vulkan(const Vulkan &) = delete;
            Vulkan &operator=(const Vulkan &) = delete;

        private:
            struct QueueFamilyIndices {
                std::optional<uint32_t> graphicsFamily;

                bool isComplete() {
                    return graphicsFamily.has_value();
                }
            };

            VkInstance instance = nullptr;
            VkPhysicalDevice physicalDevice = nullptr;

            static constexpr const char* APP_NAME = "Engine";
            static constexpr const char* ENGINE_NAME = "No Engine";
            
            const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

            #ifdef NDEBUG
                const bool enableValidationLayers = false;
            #else
                const bool enableValidationLayers = true;
            #endif

            void createInstance();

            bool checkValidationLayerSupport();

            std::vector<const char*> getRequiredExtensions();

            // -----------------------------
            // ------ PHYSICAL DEVICE ------
            // -----------------------------

            void pickPhysicalDevice();

            bool isDeviceSuitable(VkPhysicalDevice device);

            // -----------------------------
            // ----------- QUEUE -----------
            // -----------------------------

            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

            // -----------------------------
            // ---------- DEBUGGER ---------
            // -----------------------------

            VkDebugUtilsMessengerEXT debugMessenger;

            void setupDebugMessenger();

            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

            VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

            void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    };
}
