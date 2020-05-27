#include <SFML/Graphics.hpp>

#pragma once

class Obstacle
{
private:
    sf::RectangleShape obstacle_;
    sf::Texture texture_;
public:
    explicit Obstacle();
    sf::RectangleShape& getObstacle();
    void move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i);
    void draw(sf::RenderWindow& window);
    static Obstacle* createObstacles(size_t windowWidth);
};