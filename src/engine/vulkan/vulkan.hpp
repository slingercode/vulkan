#pragma once

#include "window.hpp"

#include <glm.hpp>
#include <vulkan/vulkan.h>

#include <set>
#include <array>
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

            void drawFrame();

            void waitForDevice();

        private:
            struct Vertex {
                glm::vec2 position;
                glm::vec3 color;

                static VkVertexInputBindingDescription getBindingDescription() {
                    VkVertexInputBindingDescription bindingDescription{};
                    bindingDescription.binding = 0;
                    bindingDescription.stride = sizeof(Vertex);
                    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                    return bindingDescription;
                }

                static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
                    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
                    
                    // Position
                    attributeDescriptions[0].binding = 0;
                    attributeDescriptions[0].location = 0;
                    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
                    attributeDescriptions[0].offset = offsetof(Vertex, position);

                    // Color
                    attributeDescriptions[1].binding = 0;
                    attributeDescriptions[1].location = 1;
                    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
                    attributeDescriptions[1].offset = offsetof(Vertex, color);

                    return attributeDescriptions;
                }
            };

            const std::vector<Vertex> vertices = {
                {{-0.5, 0.5}, {1.0, 0.0, 0.0}},
                {{0.0, -0.5}, {0.0, 1.0, 0.0}},
                {{0.5, 0.5}, {0.0, 0.0, 1.0}},
            };

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

            uint32_t currentFrame = 0;

            VkExtent2D swapChainExtent;
            VkFormat swapChainImageFormat;
            std::vector<VkImage> swapChainImages;
            std::vector<VkImageView> swapChainImageViews;
            std::vector<VkFramebuffer> swapChainFramebuffers;

            /// @brief Reference to the application window
            Engine::Window* window = nullptr;

            VkDevice device = nullptr;
            VkInstance vulkan = nullptr;
            VkQueue presentQueue = nullptr;
            VkSurfaceKHR surface = nullptr;
            VkBuffer vertexBuffer = nullptr;
            VkRenderPass renderPass = nullptr;
            VkSwapchainKHR swapChain = nullptr;
            VkCommandPool commandPool = nullptr;
            VkPipeline graphicsPipeline = nullptr;
            VkPipelineLayout pipelineLayout = nullptr;
            VkDeviceMemory vertexBufferMemory = nullptr;
            /// @note This object is automatically destroyed when `device (VkInstance)` is destroyed
            VkQueue graphicsQueue = nullptr;
            /// @note This object is automatically destroyed when `instance (VkDevice)` is destroyed
            VkPhysicalDevice physicalDevice = nullptr;

            std::vector<VkFence> inFlightFences;
            /// @note This object is automatically freed when the `commandPool (VkCommandPool)` is destroyed
            std::vector<VkCommandBuffer> commandBuffers;
            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;

            static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
            static constexpr const char* APP_NAME = "Engine";
            static constexpr const char* ENGINE_NAME = "No Engine";
            static constexpr const char* SHADER_MAIN_FUNCTION = "main";
            static constexpr const char* BASE_VERTEX_SHADER = "./shaders/vert.spv";
            static constexpr const char* BASE_FRAGMENT_SHADER = "./shaders/frag.spv";
            /// @note This device extension is required at least in Apple M lineups
            static constexpr const char* PHYSICAL_DEVICE_PROPERTIES_2 = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME;

            const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

            /// @note This device extensions are required at least in Apple M lineups
            const std::vector<const char*> deviceExtensions = {
                "VK_KHR_portability_subset",
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

            // CONFIGURATION

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

            void recreateSwapChain();

            void cleanupSwapChain();

            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

            // IMAGES

            void createImageViews();

            // GRAPHICS PIPELINE

            void createRenderPass();

            void createGraphicsPipeline();

            void createFramebuffers();

            void createCommandPool();

            void createCommandBuffers();

            void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

            void createSyncObjects();

            // VERTEX BUFFER

            void createVertexBuffer();

            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

            // UTILS

            static std::vector<char> readFile(const std::string& filename) {
                std::ifstream file(filename, std::ios::ate | std::ios::binary);

                if (!file.is_open()) {
                    throw std::runtime_error("Failed to open the file: " + filename);
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
