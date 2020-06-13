#include "HealthScore.h"

namespace cs = constants;

HealthScore::HealthScore()
{
    texture_.loadFromFile(cs::ResourcePath + cs::lifeTexture);
    for (auto i = 0; i < numberHearts_; i++)
    {
        sf::RectangleShape heart;
        heart.setSize(sf::Vector2f(cs::heartSizeX, cs::heartSizeY));
        heart.setTexture(&texture_);
        heart.setPosition(cs::heartPostitions[i]);
        hearts_.push_back(heart);
    }
}

void HealthScore::draw(sf::RenderWindow& window)
{
    for (auto i = 0; i < numberHearts_; i++)
    {
        window.draw(hearts_[i]);
    }
}

void HealthScore::deductHealth()
{
    numberHearts_--;
}

