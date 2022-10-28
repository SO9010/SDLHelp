cmake_minimum_required(VERSION 3.23)
project(SDLHelp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_link_options(-lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lstdc++)

add_executable(SDLHelp
        GameClass.hpp
        newMain.cpp
        Pieces.hpp)
