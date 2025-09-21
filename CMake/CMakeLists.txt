cmake_minimum_required(VERSION 3.15)
project(add_numbers LANGUAGES CXX)

add_library(mathlib src/math.cpp)
target_include_directories(mathlib PUBLIC include)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE mathlib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
