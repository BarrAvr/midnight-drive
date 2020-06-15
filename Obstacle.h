#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "Player.h"
#include "Score.h"

#pragma once

class Obstacle : public virtual Drawable
{
private:
    sf::Sprite obstacle_;
    sf::Texture texture_;
    Score& score_;
public:
    explicit Obstacle(Score& score);

    ~Obstacle() = default;

    sf::Sprite& getObstacle();

    void move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i, float speedMultiplier);

    void draw(sf::RenderWindow& window) override;

    static Obstacle* createObstacles(Score& score);
};
