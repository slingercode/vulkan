cmake_minimum_required(VERSION 3.30)

project(TestVulkan)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

set(GLFW_SDK_PATH "/opt/homebrew/Cellar/glfw/3.4")
set(VULKAN_SDK_PATH "/Users/slingercode/Documents/develop/VulkanSDK/1.3.290.0/macOS")

file(GLOB_RECURSE SRC "src/*.cpp")

file(GLOB_RECURSE HEADER_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.hpp")
foreach(_headerFile ${HEADER_DIRS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND HEADER_DIR_LIST ${_dir})
endforeach()

list(REMOVE_DUPLICATES HEADER_DIR_LIST)

include_directories(${HEADER_DIR_LIST} ${VULKAN_SDK_PATH}/include ${GLFW_SDK_PATH}/include)

link_directories(${VULKAN_SDK_PATH}/lib ${GLFW_SDK_PATH}/lib)

# Debug mode configuration
add_executable(debug ${SRC})
target_link_libraries(debug vulkan glfw3)

if (APPLE)
    target_link_libraries(debug "-framework Cocoa" "-framework IOKit")
endif()

# Release mode configuration
add_executable(release ${SRC})
target_link_libraries(release vulkan glfw3)

if (APPLE)
    target_link_libraries(release "-framework Cocoa" "-framework IOKit")
endif()
