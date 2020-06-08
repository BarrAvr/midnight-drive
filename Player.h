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
    sf::RectangleShape getPlayer();
    const float getX() { return player_.getPosition().x; };
    const float getY() { return player_.getPosition().y; };
    const float getWidth() { return player_.getSize().x; };
    const float getHeight() { return player_.getSize().y; };
    void setHealth(int newHealth) { health = newHealth; };
    int getHealth() { return health; };
private:
    sf::RectangleShape player_;
    sf::Texture texture_;
    int currentLane = 2;
    Movement movingToLane_ = Movement::NONE;
    int health;
};
