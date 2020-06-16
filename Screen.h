#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Screen
{
protected:
    sf::Font font;
    std::vector<sf::Text> menuText;
public:
    Screen() = default;
    virtual void draw(sf::RenderWindow& window) {}
    virtual void hoverSelected(int selection) {}
};
