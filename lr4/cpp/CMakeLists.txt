cmake_minimum_required(VERSION 3.10)
project(lr4_lazyseq LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
	catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.13.10
)
FetchContent_MakeAvailable(catch2)

add_subdirectory(src)
