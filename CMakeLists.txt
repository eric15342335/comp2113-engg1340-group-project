# Usage: `cmake .` and run `make` to build the project.
cmake_minimum_required(VERSION 3.22.1)
project(stocksim)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic-errors")

add_library(stock OBJECT stock.cpp)
add_library(random_price OBJECT random_price.cpp)
add_library(events OBJECT events.cpp)
add_library(names OBJECT names.cpp)
add_library(graph OBJECT graph.cpp)

add_executable(stocksim main.cpp)

target_link_libraries(stocksim
    stock
    random_price
    events
    names
    graph
)
