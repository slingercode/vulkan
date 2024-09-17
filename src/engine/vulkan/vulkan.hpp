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

            VkDevice device = nullptr;
            VkInstance instance = nullptr;
            /// @note This object is automatically destroyed when `device (VkInstance)` is destroyed
            VkQueue graphicsQueue = nullptr;
            /// @note This object is automatically destroyed when `instance (VkDevice)` is destroyed
            VkPhysicalDevice physicalDevice = nullptr;

            static constexpr const char* APP_NAME = "Engine";
            static constexpr const char* ENGINE_NAME = "No Engine";
            /// @note This device extension is required at least in Apple M lineups
            static constexpr const char* PHYSICAL_DEVICE_PROPERTIES_2 = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME;
            
            const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

            /// @note This device extensions are required at least in Apple M lineups
            const std::vector<const char*> deviceExtensions = { "VK_KHR_portability_subset" };

            #ifdef NDEBUG
                const bool enableValidationLayers = false;
            #else
                const bool enableValidationLayers = true;
            #endif

            void createInstance();

            bool checkValidationLayerSupport();

            std::vector<const char*> getInstanceRequiredExtensions();

            // PHYSICAL DEVICE

            void pickPhysicalDevice();

            bool isDeviceSuitable(VkPhysicalDevice device);

            // QUEUE

            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

            // LOGICAL DEVICE

            void createLogicalDevice();

            // DEBUGGER

            VkDebugUtilsMessengerEXT debugMessenger;

            void setupDebugMessenger();

            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

            VkResult createDebugUtilsMessenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

            void destroyDebugUtilsMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    };
}
