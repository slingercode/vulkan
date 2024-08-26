#include "application.hpp"

namespace engine {
    void application::run() {
        while (!window.shouldClose()) {
            glfwPollEvents();
        }
    }
}
