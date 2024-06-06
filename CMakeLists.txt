# MinGW Makefiles workaround: Minimum version 3.17
# github.com/Kitware/CMake/commit/82ddcf
# Tested on windows
cmake_minimum_required(VERSION 3.17)

project(stocksim)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Usage: -DOUTPUT_NAME=stocksim-cmake
# Check if the OUTPUT_NAME flag is provided
if(DEFINED OUTPUT_NAME)
    # Set the output name to the provided value
    set(OUTPUT_NAME ${OUTPUT_NAME})
else()
    # Set the output name to "stocksim"
    set(OUTPUT_NAME "stocksim")
endif()

add_executable(${OUTPUT_NAME}
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

# Works correctly for both single and multi-config generators
target_compile_definitions(${OUTPUT_NAME} PRIVATE
  $<$<CONFIG:Debug>:DEBUG_BUILD>
)

target_include_directories(${OUTPUT_NAME} PRIVATE include)

install(TARGETS ${OUTPUT_NAME} DESTINATION .)
