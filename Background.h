#pragma once
#include <SFML/Graphics.hpp>
#include "Drawable.h"

class Background : public Drawable
{
private:
    sf::Texture bgTexture;
    sf::RectangleShape background1, background2;
public:
    Background();
    ~Background() = default;
    void changeBackground(sf::RenderWindow& window, float speedMultiplier);
    void draw(sf::RenderWindow& window) override;
};
