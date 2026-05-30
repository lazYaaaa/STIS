cmake_minimum_required(VERSION 3.10)
project(ROFL_LR4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Верхнеуровневый CMake для удобной сборки из каталога lr4
add_subdirectory(cpp)
