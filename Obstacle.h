#pragma once
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Score.h"

class Obstacle
{
protected:
    Score& score;
    int damageLevel;
    sf::Sprite obstacle;
    sf::Texture obstacleTexture;
    sf::SoundBuffer crashBuffer;
    sf::Sound crashSound;
    virtual void makeCrashSound() = 0;

public:
    explicit Obstacle(Score& score, int damage_level);
    virtual ~Obstacle() = default;
    virtual std::string type() const = 0;
    void crashInToCar(Player& player) { player.getHit(Player::Damage::HIT, damageLevel); makeCrashSound(); }

    void move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i, float speedMultiplier);
    void draw(sf::RenderWindow& window);

    int getDamage() { return damageLevel; }
    sf::Sprite& getObstacle() { return obstacle; }
};