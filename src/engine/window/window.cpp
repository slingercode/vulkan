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

        glfwSetWindowUserPointer(window, this);

        glfwSetKeyCallback(window, onEscapePress);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    GLFWwindow* Window::getInstance() const {
        return window;
    }

    bool Window::getFramebufferResized() const {
        return framebufferResized;
    }

    void Window::setFramebufferResized(bool _framebufferResized) {
        framebufferResized = _framebufferResized;
    }

    void Window::onEscapePress(GLFWwindow* _window, int key, int scancode, int action, int mods) {
        /* Unused parameters */
        (void)scancode;
        (void)mods;

        if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(_window, GLFW_TRUE);
        }
    }

    void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        /* Unused parameters */
        (void)width;
        (void)height;

        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (self) {
            self->setFramebufferResized(true);
        }
    }
}
