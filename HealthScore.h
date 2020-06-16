#pragma once
#include "Constants.h"
#include "Drawable.h"

namespace cs = constants;

class HealthScore : public virtual Drawable
{
private:
    int numHearts = cs::INITIAL_HEARTS;
    sf::Texture texture;
    std::vector<sf::RectangleShape> hearts;

public:
    HealthScore();
    ~HealthScore() = default;
    void draw(sf::RenderWindow& window) override;
    void deductHealth(int damage_level = 1);
    int getHealth() const { return numHearts; }
};
