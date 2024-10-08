#include "application.hpp"

namespace Engine {
    Application::Application(Engine::Window::Configuration windowConfiguration) : window(windowConfiguration), vulkan(&window) {}

    void Application::run() {
        while (!window.shouldClose()) {
            glfwPollEvents();

            vulkan.drawFrame();
        }

        vulkan.waitForDevice();
    }
}
