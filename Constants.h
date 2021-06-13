#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>

namespace constants
{
    const std::string RESOURCE_PATH{"../Resources/"};

    const std::array<std::string, 6> OBSTACLE_FILENAMES
            {
                    "Trash can.png",
                    "Traffic cone.png",
                    "Street barricade.png",
                    "Oil can.png",
                    "Pot hole.png",
                    "Speed sign broken.png",
            };

    const std::string BACKGROUND = "background.png";

    constexpr auto WINDOW_WIDTH = 1000;
    constexpr auto WINDOW_HEIGHT = 800;
    constexpr auto FRAME_RATE = 60;
    constexpr auto PLAYER_STARTING_POS_X = 485;
    constexpr auto PLAYER_STARTING_POS_Y = 600;

    const int TARGET_X[4] = {342, 486, 634, 776};

    static const float PLAYER_SIZE = 5.0f;
    static const float OBSTACLE_SIZE = 5.0f;
    static const float HEART_SIZE_X = 40.0f;
    static const float HEART_SIZE_Y = 38.0f;

    static std::string CAR_TEXTURE = "Car blue.png";
    static std::string CAR_HIT_TEXTURE = "Car red.png";

    const std::string MENU_BACKGROUND = "pixel_background.png";
    const std::string MENU_BACKGROUND2 = "pixel_background2.png";
    const std::string FONT = "double_pixel-7.ttf";
    const std::string BACKGROUND_MUSIC = "background_music.wav";
    const std::string CAR_START_SFX = "car_start.wav";
    const std::string BUTTON_SELECT_SFX = "button_select.wav";
    const std::string BIG_CRASH_SFX = "big_crash_sound.wav";
    const std::string SMALL_CRASH_SFX = "small_crash_sound.wav";
    const std::string GAS_CRASH_SOUND = "gas_crash_sound.wav";


    const std::string LIFE_TEXTURE = "heart.png";

    const std::vector<sf::Vector2f> MENU_POSITIONS
            {
                    sf::Vector2f(WINDOW_WIDTH / 9.4, 50),
                    sf::Vector2f(WINDOW_WIDTH / 2.28, WINDOW_HEIGHT / 3.8),
                    sf::Vector2f(WINDOW_WIDTH / 2.54, WINDOW_HEIGHT / 2.6),
                    sf::Vector2f(WINDOW_WIDTH / 2.97, WINDOW_HEIGHT / 2.0),
                    sf::Vector2f(WINDOW_WIDTH / 2.26, WINDOW_HEIGHT / 1.62),
            };

    const std::vector<std::string> MENU_STRINGS
            {
                    "MIDNIGHT DRIVE",
                    "Play",
                    "Controls",
                    "Instructions",
                    "Exit"
            };

    const std::vector<double> MENU_OUTLINE_THICKNESS{3, 4, 2.5, 2.5, 2.5, 2.5};
    const std::vector<sf::Color> MENU_FILL_COLOR{sf::Color(226, 183, 10), sf::Color::Blue, sf::Color::Black,
                                               sf::Color::Black, sf::Color::Black};
    const int MENU_TITLE_SIZE = 140;
    const int MENU_OPTIONS_SIZE = 80;
    const std::pair<sf::Color, float> HOVER_ON_COLOR = {sf::Color::Blue, 4};
    const std::pair<sf::Color, float> HOVER_OFF_COLOR = {sf::Color::Black, 2.5};
    const float MENU_BG_SCALE_X = 2;
    const float MENU_BG_SCALE_Y = 2;

    const std::vector<std::string> CONTROL_STRINGS
            {
                    "Controls",
                    "<- -> arrow keys to",
                    "switch lanes",
                    "P to pause",
                    "Back"
            };

    const int CONTROL_OUTLINE_THICKNESS = 3;

    const std::vector<float> CONTROL_CHARACTER_SIZE{100, 60, 60, 80, 80};

    const std::vector<sf::Vector2f> CONTROL_POSITIONS
            {
                    sf::Vector2f(WINDOW_WIDTH / 2.78, 80),
                    sf::Vector2f(WINDOW_WIDTH / 3.0, WINDOW_HEIGHT / 3.4),
                    sf::Vector2f(WINDOW_WIDTH / 3.0, WINDOW_HEIGHT / 2.85),
                    sf::Vector2f(WINDOW_WIDTH / 3.0, WINDOW_HEIGHT / 2.0),
                    sf::Vector2f(40.0, WINDOW_HEIGHT - 120)
            };

    const std::vector<std::string> INSTRUCTIONS
            {
                    "Instructions",
                    "Avoid the obstacles",
                    "Collect gasoline to gain health",
                    "Stay sharp! Speed will",
                    "gradually increase",
                    "Back"
            };

    const int INSTRUCTION_OUTLINE_THICKNESS = 3;

    const std::vector<float> INSTRUCTION_CHARACTER_SIZE{100, 65, 65, 60, 60, 80};

    const std::vector<sf::Vector2f> INSTRUCTION_POSITIONS
            {
                    sf::Vector2f(WINDOW_WIDTH / 3.18, 80),
                    sf::Vector2f(WINDOW_WIDTH / 3.35, WINDOW_HEIGHT / 4.0),
                    sf::Vector2f(WINDOW_WIDTH / 5.7, WINDOW_HEIGHT / 2.8),
                    sf::Vector2f(WINDOW_WIDTH / 3.4, WINDOW_HEIGHT / 2.17),
                    sf::Vector2f(WINDOW_WIDTH / 3.0, WINDOW_HEIGHT / 1.87),
                    sf::Vector2f(40.0, WINDOW_HEIGHT - 120)
            };

    const std::vector<sf::Vector2f> HEART_POSITIONS
            {
                    sf::Vector2f(30, 30),
                    sf::Vector2f(80, 30),
                    sf::Vector2f(130, 30),
                    sf::Vector2f(180, 30),
                    sf::Vector2f(230, 30)
            };

    const std::int32_t HIT_DELAY(1000);

    const float BASE_OBSTACLE_MOVE_SPEED = 8.f;
    const float BASE_BACKGROUND_MOVE_SPEED = 8.f;
    const float BASE_PLAYER_MOVE_SPEED = 12.f;

    constexpr auto MAIN_MENU_TITLE = "Midnight Drive : Main Menu";
    constexpr auto GAME_WINDOW_TITLE = "Midnight Drive";
    constexpr auto GAME_OVER_TITLE = "Midnight Drive : Game Over";

    const int INITIAL_HEARTS = 5;

    const std::string SCOREBOARD_PATH = RESOURCE_PATH + "scores.txt";

    const float PAUSE_X_SCALE = 2.0;
    const float PAUSE_Y_SCALE = 2.0;
    const float PAUSE_X = 30.0;
    const float PAUSE_Y = 200.0;
    const int PAUSE_SIZE = 30;

}
