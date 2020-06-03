cmake_minimum_required(VERSION 3.13)
project(game_updated)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window network graphics audio)

add_executable(game_updated main.cpp Background.cpp Background.h Car.cpp Car.h Constants.h GameState.cpp GameState.h MainMenu.cpp MainMenu.h Obstacle.cpp Obstacle.h Player.cpp Player.h Screen.h ControlMenu.cpp ControlMenu.h)
target_link_libraries (game_updated sfml-graphics sfml-window sfml-system sfml-audio)