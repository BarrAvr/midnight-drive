#include "HealthScore.h"

HealthScore::HealthScore()
{
    texture.loadFromFile(cs::RESOURCE_PATH + cs::LIFE_TEXTURE);
    for (auto i = 0; i < numHearts; i++)
    {
        sf::RectangleShape heart;
        heart.setSize(sf::Vector2f(cs::HEART_SIZE_X, cs::HEART_SIZE_Y));
        heart.setTexture(&texture);
        heart.setPosition(cs::HEART_POSITIONS[i]);
        hearts.push_back(heart);
    }
}

void HealthScore::draw(sf::RenderWindow& window)
{
    for (auto i = 0; i < numHearts; i++)
    {
        window.draw(hearts[i]);
    }
}

void HealthScore::deductHealth(int damage_level)
{
    if(numHearts - damage_level <= cs::INITIAL_HEARTS)
    {
        numHearts -= damage_level;
    }
}
