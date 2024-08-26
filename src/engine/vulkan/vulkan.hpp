#pragma once

#include "GLFW/glfw3.h"
#include "vulkan/vulkan.hpp"

namespace engine {
    class vulkan {
        private:
            VkInstance instance = nullptr;
            static constexpr const char* APP_NAME = "Engine";
            static constexpr const char* ENGINE_NAME = "No Engine";

            void init();

            void createInstance();

        public:
            vulkan();
            ~vulkan();

            vulkan(const vulkan &) = delete;
            vulkan &operator=(const vulkan &) = delete;
    };
}
