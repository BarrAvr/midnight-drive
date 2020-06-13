#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"

class MainMenu : public virtual Screen
{
private:
    sf::Event menuScreen{};
    sf::Music music, carDriving;
    sf::SoundBuffer buffer;
    sf::Sound button;
    int selectedItemIndex = 0;
    sf::RenderWindow window_;
public:
    MainMenu();

    ~MainMenu();

    bool startMenu();

    void draw();

    void Move();

    void hoverSelected(int selection) override;

    int getSelectedItemIndex() const
    { return selectedItemIndex; }
};
