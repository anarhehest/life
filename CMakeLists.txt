cmake_minimum_required(VERSION 3.12)

project(GameOfLife C)

include_directories(.)

find_package(SDL2 2.0.23 REQUIRED COMPONENTS SDL2main)

add_executable(GameOfLife
        main.c
        grid.c
)

target_link_libraries(GameOfLife
        SDL2::SDL2main
        SDL2::SDL2-static
)