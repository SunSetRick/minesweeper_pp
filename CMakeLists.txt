cmake_minimum_required(VERSION 3.20)
project(minesweeper VERSION 0.0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(minesweeper
    src/main.cpp
    src/board.cpp
)

option(ENABLE_ASAN "Enable AddressSanitizer " ON)

if (ENABLE_ASAN)
    target_compile_options(minesweeper PRIVATE 
        -fsanitize=address
        -fno-omit-frame-pointer 
        -g 
    )
    target_link_options(minesweeper PRIVATE
        -fsanitize=address
    )
endif()

