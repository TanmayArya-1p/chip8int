cmake_minimum_required(VERSION 3.10)
project(chip8int)
set(CMAKE_CXX_STANDARD 23)
add_executable(chip8
    src/main.cpp
    src/chip8.cpp
    src/memory.cpp
    src/display.cpp
    src/input.cpp
    src/interpreter.cpp
)
target_include_directories(chip8 PRIVATE include)
