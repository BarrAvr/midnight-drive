#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "FileNotFound.h"
#include "Background.h"
#include "Constants.h"

namespace cs = constants;

Background::Background()
{
    background1.setSize(sf::Vector2f(cs::WINDOW_WIDTH, cs::WINDOW_HEIGHT + 40));
    background2.setSize(sf::Vector2f(cs::WINDOW_WIDTH, cs::WINDOW_HEIGHT + 40));

    std::string texturePath = cs::RESOURCE_PATH + cs::BACKGROUND;
    while (!bgTexture.loadFromFile(texturePath))
    {
        try { throw FileNotFound("Background texture\n"); }
        catch (FileNotFound e)
        {
            texturePath = e.resolve();
            if (texturePath == "")
                break;
        }
    }

    background1.setTexture(&bgTexture);
    background2.setTexture(&bgTexture);
    background2.setPosition(sf::Vector2f(0, -cs::WINDOW_HEIGHT));
}

// Background Scrolling
void Background::changeBackground(sf::RenderWindow& window, float speedMultiplier)
{
    if(background1.getPosition().y < window.getSize().y || background2.getPosition().y < window.getSize().y)
    {
        background1.move(sf::Vector2f(0, cs::BASE_BACKGROUND_MOVE_SPEED * speedMultiplier));
        background2.move(sf::Vector2f(0, cs::BASE_BACKGROUND_MOVE_SPEED * speedMultiplier));

        if (background1.getPosition().y >= 780)
        {
            background1.setPosition(sf::Vector2f(0, -800));
        } 
        if (background2.getPosition().y >= 780)
        {
            background2.setPosition(sf::Vector2f(0, -800));
        }
    }
}

void Background::draw(sf::RenderWindow& window)
{
    window.draw(background1);
    window.draw(background2);
}
