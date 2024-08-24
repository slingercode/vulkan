#pragma once

#include <GLFW/glfw3.h>

#include <string>

#define GLFW_INCLUDE_VULKAN

namespace engine {
  class window {
    private:
        GLFWwindow* instance = nullptr;
        int width = 0;
        int height = 0;
        std::string name = "";

        void init();

        static void closeWindowWithEscapeCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
        window(int width, int height, std::string name);
        ~window();
        
        window(const window &) = delete;
        window &operator=(const window &) = delete;

        bool shouldClose();
  };
}
