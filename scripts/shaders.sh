#!/bin/sh

mkdir -p ./build/shaders

/Users/slingercode/Documents/develop/VulkanSDK/1.3.290.0/macOS/bin/glslc ./src/engine/shaders/base.vert -o ./build/shaders/vert.spv
/Users/slingercode/Documents/develop/VulkanSDK/1.3.290.0/macOS/bin/glslc ./src/engine/shaders/base.frag -o ./build/shaders/frag.spv
