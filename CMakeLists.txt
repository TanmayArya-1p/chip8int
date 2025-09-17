cmake_minimum_required(VERSION 3.10)
project(chip8int)
set(CMAKE_CXX_STANDARD 23)
add_executable(chip8
    src/main.cpp
    # src/chip8.cpp
    src/memory.cpp
    src/display.cpp
    src/instruction.cpp
    src/input.cpp
    src/interpreter.cpp
)

find_package(SDL2 REQUIRED)
target_include_directories(chip8 PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(chip8 PRIVATE ${SDL2_LIBRARIES})
target_include_directories(chip8 PRIVATE include)
