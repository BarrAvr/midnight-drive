#pragma once

#include "Constants.h"

class HealthScore
{
private:
    int numberHearts_ = constants::initialHearts;
    sf::Texture texture_;
    std::vector<sf::RectangleShape> hearts_;

public:
    HealthScore();
    ~HealthScore() = default;
    void draw(sf::RenderWindow& window);
    void deductHealth();
    int getHealth() const { return numberHearts_; }
};


