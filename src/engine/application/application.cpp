#include "application.hpp"

namespace Engine {
    Application::Application(Engine::Window::Configuration windowConfiguration) : window(windowConfiguration) {}

    void Application::run() {
        while (!window.shouldClose()) {
            glfwPollEvents();
        }
    }
}
