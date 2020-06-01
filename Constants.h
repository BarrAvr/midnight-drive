#pragma once

#include <array>
#include <iostream>
#include <vector>
#include "ResourcePath.hpp"

namespace constants
{
    //const std::string ResourcePath{"/home/dlieber/Downloads/Car_game_v4/"};

    const std::array<std::string_view, 15> PATHS
            {
                    //"Car grey front.png",
                    "Trash can fallen.png",
                    "Traffic cone.png",
                    "Street baracade.png",
                    //"Car yellow front.png",
                    //"Construction sign.png",
                    "Oil can.png",
                    //"Left sign broken.png",
                    //"Right sign broken.png",
                    "Speed sign broken.png",
                    //"Stop sign broken.png",
                    //"Stripped sign 1.png",
                    //"Pot hole.png",
                    //"Oil spill.png",
                    //"Man hole.png"
            };
    /*
    const std::vector<std::string> backgrounds_{"b0.png", "b1.png", "b2.png",
                                          "b3.png", "b4.png",
                                          "b5.png", "b6.png",
                                          "b7.png", "b8.png", "b9.png"};
    */
    const std::string background_ = "background.png";

    constexpr auto WindowWidth_ = 1000;
    constexpr auto WindowHeight_ = 800;
    constexpr auto frameRate_ = 30;
    constexpr auto playerStartingPosX = 465;
    constexpr auto playerStartingPosY = 590;

    const int targetX_[4] = { 310, 465, 605, 755 };

    static const float playerSize = 200.0f;

    static const float obstacleSize = 170.0f;

    static std::string carTexture = "Car blue.png";




}
