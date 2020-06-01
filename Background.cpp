#include "Background.h"
#include <cassert>
#include "Constants.h"

Background::Background()
{
    background1_.setSize(sf::Vector2f(constants::WindowWidth_, constants::WindowHeight_));
    background2_.setSize(sf::Vector2f(constants::WindowWidth_, constants::WindowHeight_));
    bgTexture1.loadFromFile(resourcePath() + constants::background_);
    background1_.setTexture(&bgTexture1);

    bgTexture2.loadFromFile(resourcePath() + constants::background_);
    background2_.setTexture(&bgTexture2);
    background2_.setPosition(sf::Vector2f(0, -constants::WindowHeight_));
    //background_.setSize(sf::Vector2f(constants::WindowWidth_, constants::WindowHeight_));
}

//void Background::changeBackground()
void Background::changeBackground(sf::RenderWindow& window)
{
   /*
    bgChangeCounter_++;
    if (bgChangeCounter_ == 6)
    {
        currBg_++;
        bgChangeCounter_ = 0;
    }

    if (currBg_ > constants::backgrounds_.size() - 1)
    {
        currBg_ = 0;
    }

    assert(texture_.loadFromFile(resourcePath() + constants::backgrounds_.at(currBg_)));
    */
    
    //Scrolling background
    if(background1_.getPosition().y < window.getSize().y || background2_.getPosition().y < window.getSize().y)
    {
        background1_.move(sf::Vector2f(0, 10));
        background2_.move(sf::Vector2f(0, 10));
        if(background1_.getPosition().y == 800)
            background1_.setPosition(sf::Vector2f(0, -780));
        if(background2_.getPosition().y == 800)
            background2_.setPosition(sf::Vector2f(0, -780));
    }
    
    
}

void Background::draw(sf::RenderWindow& window)
{
    //window.draw(background_);
    window.draw(background1_);
    window.draw(background2_);
}
