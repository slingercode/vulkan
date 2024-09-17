#include "application.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

static const Engine::Window::Configuration windowConfiguration = {
    1200,
    600,
    "Vulkan"
};

int main() {
    Engine::Application app(windowConfiguration);

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
