#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Background
{
private:
    sf::Texture bgTexture1, bgTexture2;
    sf::RectangleShape background1_, background2_;
public:
    Background();

    ~Background() = default;

    void changeBackground(sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);
};
