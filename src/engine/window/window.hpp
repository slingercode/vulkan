#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <string>

namespace Engine {
    class Window {
        public:
            struct Configuration {
                uint32_t width;
                uint32_t height;
                std::string name;
                
                Configuration(uint32_t width, uint32_t height, const std::string& name) : width(width), height(height), name(name) {}
            };

            Window(Configuration configuration);
            ~Window();
            
            Window(const Window &) = delete;
            Window &operator=(const Window &) = delete;

            bool shouldClose();

        private:
            GLFWwindow* window = nullptr;
            Configuration configuration;

            void init();

            static void onEscapePress(GLFWwindow* window, int key, int scancode, int action, int mods);
    };
}
