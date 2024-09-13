#!/bin/sh

mkdir -p build && cd build

cmake -DCMAKE_BUILD_TYPE=debug ..
cmake --build . --target debug

# Release mode
# cmake -DCMAKE_BUILD_TYPE=release ..
# cmake --build . --target release
