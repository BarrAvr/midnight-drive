#pragma once

#include <SFML/Graphics.hpp>
#include "HealthScore.h"
#include "Drawable.h"

class Player : public virtual Drawable
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
    void movePlayer(float speedMultiplier);
    void draw(sf::RenderWindow& window) override;
    sf::Sprite getPlayer();
    void getHit(Damage dmg, int damage_level = 1);

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
