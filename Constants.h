#pragma once

#include <array>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace constants
{
    const std::string ResourcePath{"/home/dlieber/Downloads/Car_game_v4/"};

    const std::array<std::string_view, 5> PATHS
            {
                    "Trash can fallen.png",
                    "Traffic cone.png",
                    "Street baracade.png",
                    "Oil can.png",
                    "Speed sign broken.png",
            };

    const std::string background_ = "background.png";

    constexpr auto WindowWidth_ = 1000;
    constexpr auto WindowHeight_ = 800;
    constexpr auto frameRate_ = 30;
    constexpr auto playerStartingPosX = 465;
    constexpr auto playerStartingPosY = 590;

    const int targetX_[4] = { 310, 465, 605, 755 };

    static const float playerSize = 200.0f;

    static const float obstacleSize = 100.0f;

    static std::string carTexture = "Car blue.png";

    const std::string menuBackground = "pixel_background.png";
    const std::string font = "double_pixel-7.ttf";
    const std::string backgroundMusic = "background_music.wav";
    const std::string carStart = "car_start.wav";
    const std::string buttonSelect = "button_select.wav";

    const std::vector<sf::Vector2f> menuPositions
            {
                    sf::Vector2f(WindowWidth_ / 9.4, 50),
                    sf::Vector2f(WindowWidth_ / 2.28, WindowHeight_ / 3.8),
                    sf::Vector2f(WindowWidth_ / 2.54, WindowHeight_ / 2.6),
                    sf::Vector2f(WindowWidth_ / 2.26, WindowHeight_ / 2.0)
            };

    const std::vector<std::string> menuStrings
            {
                    "MIDNIGHT DRIVE",
                    "Play",
                    "Controls",
                    "Exit"
            };

    const std::vector<double> menuOutlineThickness{3, 4, 2.5, 2.5};
    const std::vector<sf::Color> menuFillColor{sf::Color(226, 183, 10), sf::Color::Blue, sf::Color::Black,
                                               sf::Color::Black};
    const int menuTitleSize = 140;
    const int menuOptionsSize = 80;
    const std::pair<sf::Color, float> onHover = {sf::Color::Blue, 4};
    const std::pair<sf::Color, float> offHover = {sf::Color::Black, 2.5};
    const float menuBgScaleX = 2.5;
    const float menuBgScaleY = 2;

    const std::vector<std::string> controlStrings
            {
                    "Controls",
                    "<- -> arrow keys to",
                    "switch lanes",
                    "P to pause",
                    "Back"
            };
    const int controlOutlineThickness = 3;

    const std::vector<float> controlCharacterSize {100, 60, 60, 80, 80};

    const std::vector<sf::Vector2f> controlPositions
            {
                    sf::Vector2f(WindowWidth_ / 2.78, 80),
                    sf::Vector2f(WindowWidth_ / 3.0, WindowHeight_ / 3.4),
                    sf::Vector2f(WindowWidth_ / 3.0, WindowHeight_ / 2.85),
                    sf::Vector2f(WindowWidth_ / 3.0, WindowHeight_ / 2.0),
                    sf::Vector2f(40.0, WindowHeight_ - 120)
            };


}
