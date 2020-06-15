#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Drawable.h"

class Background : public Drawable
{
private:
    sf::Texture bgTexture1, bgTexture2;
    sf::RectangleShape background1_, background2_;
public:
    Background();

    ~Background() = default;

    void changeBackground(sf::RenderWindow& window, float speedMultiplier);

    void draw(sf::RenderWindow& window) override;
};
