#include "application.hpp"

static const Engine::Window::Configuration windowConfiguration = {
    800,
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
