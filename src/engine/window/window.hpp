#pragma once

#define GLFW_INCLUDE_VULKAN

#include "GLFW/glfw3.h"

#include "string"

namespace engine {
  class window {
    private:
        GLFWwindow* instance = nullptr;
        uint32_t width = 0;
        uint32_t height = 0;
        std::string name = "";

        void init();

        static void closeWindowWithEscapeCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    public:
        window(uint32_t width, uint32_t height, std::string name);
        ~window();
        
        window(const window &) = delete;
        window &operator=(const window &) = delete;

        bool shouldClose();
  };
}
