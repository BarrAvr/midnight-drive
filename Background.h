#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Background
{
private:
    sf::Texture texture_;
    sf::RectangleShape background_;
    int currBg_ = 0;
    int bgChangeCounter_ = 0;

public:
    Background();
    ~Background() = default;

    void changeBackground();

    void draw(sf::RenderWindow& window);
};
