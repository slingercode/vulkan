#pragma once

#include "window.hpp"

#include <vulkan/vulkan.h>

#include <set>
#include <vector>
#include <fstream>
#include <optional>
#include <iostream>

namespace Engine {
    class Vulkan {
        public:
            Vulkan(Engine::Window* window);
            ~Vulkan();

            Vulkan(const Vulkan &) = delete;
            Vulkan &operator=(const Vulkan &) = delete;

        private:
            struct QueueFamilyIndices {
                std::optional<uint32_t> graphicsFamily;
                std::optional<uint32_t> presentFamily;

                bool isComplete() {
                    return graphicsFamily.has_value() && presentFamily.has_value();
                }
            };

            struct SwapChainSupportDetails {
                VkSurfaceCapabilitiesKHR capabilities;
                std::vector<VkSurfaceFormatKHR> formats;
                std::vector<VkPresentModeKHR> presentModes;
            };

            #ifdef NDEBUG
                const bool enableValidationLayers = false;
            #else
                const bool enableValidationLayers = true;
            #endif

            VkExtent2D swapChainExtent;
            VkFormat swapChainImageFormat;
            std::vector<VkImage> swapChainImages;
            std::vector<VkImageView> swapChainImageViews;

            /// @brief Reference to the application window
            Engine::Window* window = nullptr;

            VkDevice device = nullptr;
            VkInstance instance = nullptr;
            VkQueue presentQueue = nullptr;
            VkSurfaceKHR surface = nullptr;
            VkSwapchainKHR swapChain = nullptr;
            VkPipelineLayout pipelineLayout = nullptr;
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
            const std::vector<const char*> deviceExtensions = {
                "VK_KHR_portability_subset",
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

            void createInstance();

            bool checkValidationLayerSupport();

            std::vector<const char*> getInstanceRequiredExtensions();

            // SURFACE

            void createSurface();

            // PHYSICAL DEVICE

            void pickPhysicalDevice();

            bool isDeviceSuitable(VkPhysicalDevice device);

            bool checkDeviceExtensionSupport(VkPhysicalDevice device);

            // QUEUE

            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

            // LOGICAL DEVICE

            void createLogicalDevice();

            // SWAP CHAIN

            void createSwapChain();

            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

            // IMAGES

            void createImageViews();

            // GRAPHICS PIPELINE

            void createGraphicsPipeline();

            // UTILS

            static std::vector<char> readFile(const std::string& filename) {
                std::ifstream file(filename, std::ios::ate | std::ios::binary);

                if (!file.is_open()) {
                    throw std::runtime_error("failed to open file!");
                }

                size_t fileSize = (size_t) file.tellg();
                std::vector<char> buffer(fileSize);

                file.seekg(0);
                file.read(buffer.data(), fileSize);

                file.close();

                return buffer;
            }
        
            VkShaderModule createShaderModule(const std::vector<char>& code) {
                VkShaderModule shaderModule;

                VkShaderModuleCreateInfo createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
                createInfo.codeSize = code.size();
                createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

                VkResult shaderInstanceResult = vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);

                if (shaderInstanceResult != VK_SUCCESS) {
                    const std::string msg = "Failed to create a Vulkan shader module. [CODE]: " + std::to_string(shaderInstanceResult);
                    throw std::runtime_error(msg);
                }

                return shaderModule;
            }

            // DEBUGGER

            VkDebugUtilsMessengerEXT debugMessenger;

            void setupDebugMessenger();

            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

            VkResult createDebugUtilsMessenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

            void destroyDebugUtilsMessenger(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    };
}
