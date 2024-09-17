#include "window.hpp"

namespace Engine {
    Window::Window(Configuration configuration) : configuration(configuration) {
        init();
    }

    Window::~Window() {
        if (window != nullptr) {
            glfwDestroyWindow(window);
        }

        glfwTerminate();
    }

    void Window::init() {
        if (!glfwInit()) {
            throw std::runtime_error("There was an error trying to initialize GLFW");
        }
        
        // Disable OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // Disable window resizing
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(
            configuration.width,
            configuration.height,
            configuration.name.c_str(),
            nullptr,
            nullptr
        );

        if (window == nullptr) {
            throw std::runtime_error("There was an error trying to initialize the GLFW window context");
        }

        glfwSetKeyCallback(window, onEscapePress);
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::onEscapePress(GLFWwindow* _window, int key, int scancode, int action, int mods) {
        /* Unused parameters */
        (void)scancode;
        (void)mods;

        if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(_window, GLFW_TRUE);
        }
    }
}
