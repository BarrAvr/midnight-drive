#pragma once

#include <array>
#include <iostream>
#include <vector>


namespace constants
{
    const std::string ResourcePath{"/home/dlieber/Downloads/Car_game_v4/"};

    const std::array<std::string_view, 15> PATHS
            {
                    "Car grey front.png",
                    "Trash can fallen.png",
                    "Traffic cone.png",
                    "Street baracade.png",
                    "Car yellow front.png",
                    "Construction sign.png",
                    "Oil can.png",
                    "Left sign broken.png",
                    "Right sign broken.png",
                    "Speed sign broken.png",
                    "Stop sign broken.png",
                    "Stripped sign 1.png",
                    "Pot hole.png",
                    "Oil spill.png",
                    "Man hole.png"
            };
    const std::vector<std::string> backgrounds_{"b0.png", "b1.png", "b2.png",
                                          "b3.png", "b4.png",
                                          "b5.png", "b6.png",
                                          "b7.png", "b8.png", "b9.png"};

    constexpr auto WindowWidth_ = 640;
    constexpr auto WindowHeight_ = 480;
    constexpr auto frameRate_ = 30;
    constexpr auto playerStartingPosX = 250;
    constexpr auto playerStartingPosY = 320;

    const int targetX_[4] = {120, 250, 370, 480};

    static const float playerSize = 128.0f;

    static const float obstacleSize = 60.0f;

    static std::string carTexture = "Car blue.png";




}