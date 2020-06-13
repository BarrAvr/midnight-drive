#pragma once

#include <SFML/Graphics.hpp>
#include "HealthScore.h"

class Player
{
public:
    enum class Movement {
        NONE,
        LEFT,
        RIGHT,
    };
    enum class Damage {
        HIT,
        NOT_HIT,
    };
    explicit Player(HealthScore& healthScore);
    ~Player() = default;
    void changeLane(Movement playerDirection);
    void movePlayer();
    void draw(sf::RenderWindow& window);
    sf::Sprite getPlayer();
    void getHit(Damage dmg);

    float getX() { return player_.getPosition().x; };
    float getY() { return player_.getPosition().y; };
    float getWidth() { return player_.getScale().x; };
    float getHeight() { return player_.getScale().y; };

private:
    sf::Sprite player_;
    sf::Texture textureBlue_;
    sf::Texture textureRed_;
    int currentLane = 2;
    Movement movingToLane_ = Movement::NONE;
    Damage gettingHit_ = Damage::NOT_HIT;
    sf::Clock hitTimer_;
    HealthScore& healthScore_;

};
