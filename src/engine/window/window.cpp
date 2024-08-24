#include "window.hpp"

namespace engine {
  window::window(int width, int height, std::string name): width(width), height(height), name(name) {
    init();
  }

  window::~window() {
    glfwDestroyWindow(instance);
    glfwTerminate();
  }

  void window::init() {
    if (!glfwInit()) {
        fprintf(stderr, "Error: There was an error trying to initialize GLFW\n");

        return;
    }
    
    /* Disable OpenGL context */
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    /* Disable window resizing */
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    instance = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    /** Register ESC button to close the window */
    glfwSetKeyCallback(instance, closeWindowWithEscapeCallback);
  }

  bool window::shouldClose() {
    return glfwWindowShouldClose(instance);
  }

  void window::closeWindowWithEscapeCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /* Unused parameters */
    (void)scancode;
    (void)mods;

    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  }
}
