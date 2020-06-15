#pragma once

#include "Constants.h"
#include "Drawable.h"

namespace cs = constants;

class HealthScore : public virtual Drawable
{
private:
    int numberHearts_ = cs::initialHearts;
    sf::Texture texture_;
    std::vector<sf::RectangleShape> hearts_;

public:
    HealthScore();
    ~HealthScore() = default;
    void draw(sf::RenderWindow& window) override;
    void deductHealth();
    int getHealth() const { return numberHearts_; }
};


