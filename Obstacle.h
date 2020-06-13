#include <SFML/Graphics.hpp>
#include "Player.h"

#pragma once

class Obstacle
{
private:
    sf::Sprite obstacle_;
    sf::Texture texture_;
    int score_ = 0;
public:
    explicit Obstacle();
    ~Obstacle() = default;

    sf::Sprite& getObstacle();

    void move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i);
    void draw(sf::RenderWindow& window);

    static Obstacle* createObstacles(size_t windowWidth);
};
