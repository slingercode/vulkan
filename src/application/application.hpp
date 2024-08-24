#pragma once

#include "window.hpp"

namespace application {
    class main {
        private:
            static constexpr int width = 800;
            static constexpr int height = 600;
            engine::window window{width, height, "Vulkan"};

        public:
            void run();
    };
}
