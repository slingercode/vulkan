#include "vulkan.hpp"

namespace engine {
    vulkan::vulkan() {
        init();
    }

    vulkan::~vulkan() {
        vkDestroyInstance(instance, nullptr);
    }

    void vulkan::init() {
        createInstance();
    }

    void vulkan::createInstance() {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = APP_NAME;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = ENGINE_NAME;
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        
        uint32_t glfwExtensionCount = 0;
        std::vector<const char*> requiredExtensions;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        for (uint32_t i = 0; i < glfwExtensionCount; i++) {
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }
        
        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        createInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
        createInfo.enabledLayerCount = 0;

        const VkResult instanceResult = vkCreateInstance(&createInfo, nullptr, &instance);

        if (instanceResult != VK_SUCCESS) {
            const std::string msg = "Failed to create Vulkan instance! [CODE]: " + std::to_string(instanceResult);
            throw std::runtime_error(msg);
        }
    }
}
