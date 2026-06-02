cmake_minimum_required(VERSION 3.10)
project(STIS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable CTest from the top-level so subdirectory tests are discoverable.
include(CTest)

# Верхнеуровневый CMake для удобной сборки из каталога lr4
add_subdirectory(cpp)
