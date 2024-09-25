#pragma once

#include "window.hpp"
#include "vulkan.hpp"

namespace Engine {
    class Application {
        public:
            Application(Engine::Window::Configuration windowConfiguration);

            void run();

        private:
            Window window;
            Vulkan vulkan;
    };
}
