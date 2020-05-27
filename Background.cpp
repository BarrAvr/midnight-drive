#include "Background.h"
#include <cassert>
#include "Constants.h"

Background::Background()
{
    background_.setSize(sf::Vector2f(constants::WindowWidth_, constants::WindowHeight_));
}

void Background::changeBackground()
{
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

    assert(texture_.loadFromFile(constants::ResourcePath + constants::backgrounds_.at(currBg_)));
    background_.setTexture(&texture_);
}

void Background::draw(sf::RenderWindow& window)
{
    window.draw(background_);
}