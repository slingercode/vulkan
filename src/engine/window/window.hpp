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

            GLFWwindow* window = nullptr;
            Configuration configuration;

            Window(Configuration configuration);
            ~Window();
            
            Window(const Window &) = delete;
            Window &operator=(const Window &) = delete;

            bool shouldClose();

            bool getFramebufferResized();

            void setFramebufferResized(bool _framebufferResized);

        private:
            bool framebufferResized = false;

            void init();

            static void onEscapePress(GLFWwindow* window, int key, int scancode, int action, int mods);

            static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    };
}
