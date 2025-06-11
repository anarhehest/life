cmake_minimum_required(VERSION 3.12)

project(GameOfLife C)

include_directories(.)

find_package(SDL2 2.0.23 REQUIRED COMPONENTS SDL2main)

if(UNIX AND NOT APPLE)
    find_package(SDL_ttf REQUIRED)
    set(TTF_LIBS SDL2_ttf)
else()
    find_package(SDL2_ttf CONFIG REQUIRED)
    set(TTF_LIBS SDL2_ttf::SDL2_ttf)
endif()

add_executable(GameOfLife
        main.c
        grid.c
)

set(SDL2
        /Library/Frameworks/SDL2.framework
)
set(SDL2_ttf
        /Library/Frameworks/SDL2_ttf.framework
)

target_link_libraries(
        GameOfLife PRIVATE
        ${SDL2}/Versions/A/SDL2
        ${SDL2_ttf}/Versions/A/SDL2_ttf
)

target_include_directories(
        GameOfLife PRIVATE
        ${SDL2}/Versions/A/Headers
        ${SDL2_ttf}/Versions/A/Headers
)