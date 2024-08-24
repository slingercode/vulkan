#include "application.hpp"

#include "vulkan/vulkan.hpp"

#include "cstdlib"
#include "iostream"
#include "stdexcept"

int main() {
    // Vulkan
    VkInstance instance = nullptr;
    const VkInstanceCreateInfo createInfo = {};

    const VkResult instanceResult = vkCreateInstance(&createInfo, nullptr, &instance);

    if (instanceResult == VK_SUCCESS) {
        std::cout << "Vulkan instantiated" << '\n';
    } else {
        std::cout << "Error instantiating vulkan: [CODE " << instanceResult << "]\n";
    }

    application::main app;

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
