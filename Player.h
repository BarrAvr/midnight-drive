#pragma once
#include <SFML/Graphics.hpp>
#include "HealthScore.h"
#include "Drawable.h"

class Player : public virtual Drawable
{
public:
    enum class Movement
    {
        NONE,
        LEFT,
        RIGHT,
    };
    enum class Damage
    {
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
    sf::Texture textureBlue;
    sf::Texture textureRed;
    int currentLane = 2;
    Movement movingToLane = Movement::NONE;
    Damage gettingHit = Damage::NOT_HIT;
    sf::Clock hitTimer;
    HealthScore& healthScore;

};
