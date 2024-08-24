#include "application.hpp"

namespace application {
    void main::run() {
        while (!window.shouldClose()) {
            glfwPollEvents();
        }
    }
}
