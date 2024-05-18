# MinGW Makefiles workaround: Minimum version 3.17
# github.com/Kitware/CMake/commit/82ddcf
# Tested on windows
cmake_minimum_required(VERSION 3.17)

project(stocksim)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(stocksim
    src/main.cpp
    src/random_price.cpp
    src/file_io.cpp
    src/stock.cpp
    src/events.cpp
    src/names.cpp
    src/format.cpp
    src/draw.cpp
    src/graph.cpp
    src/controls.cpp
)

target_include_directories(stocksim PRIVATE include)
