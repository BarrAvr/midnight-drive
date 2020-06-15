#include "Background.h"
#include "Constants.h"

namespace cs = constants;

Background::Background()
{
    background1_.setSize(sf::Vector2f(cs::WindowWidth_, cs::WindowHeight_ + 40));
    background2_.setSize(sf::Vector2f(cs::WindowWidth_, cs::WindowHeight_ + 40));
    bgTexture1.loadFromFile(cs::ResourcePath + cs::background_);
    background1_.setTexture(&bgTexture1);

    bgTexture2.loadFromFile(cs::ResourcePath + cs::background_);
    background2_.setTexture(&bgTexture2);
    background2_.setPosition(sf::Vector2f(0, -cs::WindowHeight_));
}

void Background::changeBackground(sf::RenderWindow& window, float speedMultiplier)
{
    
    //Scrolling background
    if(background1_.getPosition().y < window.getSize().y || background2_.getPosition().y < window.getSize().y)
    {
        background1_.move(sf::Vector2f(0, cs::baseBackgroundMoveSpeed * speedMultiplier));
        background2_.move(sf::Vector2f(0, cs::baseBackgroundMoveSpeed * speedMultiplier));
        if(background1_.getPosition().y >= 800)
            background1_.setPosition(sf::Vector2f(0, -800));
        if(background2_.getPosition().y >= 800)
            background2_.setPosition(sf::Vector2f(0, -800));
    }
}

void Background::draw(sf::RenderWindow& window)
{
    window.draw(background1_);
    window.draw(background2_);
}
