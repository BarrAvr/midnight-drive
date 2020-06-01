#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Background
{
private:
    sf::Texture bgTexture1, bgTexture2;
    sf::RectangleShape background1_, background2_;
    //sf::RectangleShape background_;
    
    //int currBg_ = 0;
    //int bgChangeCounter_ = 0;

public:
    Background();
    ~Background() = default;

    void changeBackground(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

/*
sf::RectangleShape bg1(sf::Vector2f(1000, 800));
sf::Texture bgTexture1;
bgTexture1.loadFromFile("background.png");
bg1.setTexture(&bgTexture1);

sf::RectangleShape bg2(sf::Vector2f(1000, 800));
sf::Texture bgTexture2;
bgTexture2.loadFromFile("background.png");
bg2.setTexture(&bgTexture2);
bg2.setPosition(sf::Vector2f(0, -800));
*/
