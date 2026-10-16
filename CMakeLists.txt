cmake_minimum_required(VERSION 3.20)
project(minesweeper VERSION 0.0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(minesweeper 
    src/main.cpp
    src/board.cpp
)

if (MSVC)
    target_compile_options(minesweeper PRIVATE /W4)
else()
    target_compile_options(minesweeper PRIVATE -Wall -Wextra -Wpedantic)
endif()

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

if (ENABLE_ASAN AND NOT MSVC)
    target_compile_options(minesweeper PRIVATE 
        -fsanitize=address
        -fno-omit-frame-pointer 
        -g 
    )
    target_link_options(minesweeper PRIVATE
        -fsanitize=address
    )
endif()

