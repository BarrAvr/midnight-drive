cmake_minimum_required(VERSION 3.2)
project(MidnightDriveMaster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp Background.cpp
        ControlMenu.cpp GameState.cpp MainMenu.cpp
        Obstacle.cpp Player.cpp Scoreboard.cpp
        Collision.cpp GameOver.cpp HealthScore.cpp NameInput.cpp
        barricade.cpp cone.cpp gasoline.cpp Pothole.cpp Score.cpp
        Streetsign.cpp Trashcan.cpp FileNotFound.cpp Instructions.cpp)
add_executable(MidnightDriveMaster ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MidnightDriveMaster ${SFML_LIBRARIES})
endif()