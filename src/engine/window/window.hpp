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
            };

            Configuration configuration;

            Window(Configuration configuration);
            ~Window();
            
            Window(const Window &) = delete;
            Window &operator=(const Window &) = delete;

            bool shouldClose();

            GLFWwindow* getInstance() const;

            bool getFramebufferResized() const;

            void setFramebufferResized(bool _framebufferResized);

        private:
            GLFWwindow* window = nullptr;
            bool framebufferResized = false;

            void init();

            static void onEscapePress(GLFWwindow* window, int key, int scancode, int action, int mods);

            static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    };
}
