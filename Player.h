#pragma once

#include <SFML/Graphics.hpp>


class Player
{
public:
    enum class Movement {
        NONE,
        LEFT,
        RIGHT,
    };
    Player();
    ~Player() = default;
    void changeLane(Movement playerDirection);
    void movePlayer();
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape player_;
    sf::Texture texture_;
    int currentLane = 2;
    Movement movingToLane_ = Movement::NONE;
};
