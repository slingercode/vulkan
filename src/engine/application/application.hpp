#pragma once

#include "window.hpp"
#include "vulkan.hpp"

namespace engine {
    class application {
        private:
            static constexpr uint32_t width = 800;
            static constexpr uint32_t height = 600;
            engine::window window = {width, height, "Vulkan"};
            engine::vulkan vulkan = {};

        public:
            void run();
    };
}
