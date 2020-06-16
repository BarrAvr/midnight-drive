#pragma once
#include <iostream>
#include "Screen.h"

class MainMenu : public virtual Screen
{
private:
    sf::RenderWindow menuWindow;
    sf::Event menuScreen{};
    sf::Music music;
    sf::SoundBuffer buffer;
    sf::Sound button;
    int selectedItemIndex = 0;

public:
    MainMenu();
    ~MainMenu();

    bool startMenu();
    void draw();
    void move();
    void hoverSelected(int selection) override;
    int getSelectedItemIndex() const
    {
        return selectedItemIndex;
    }
};
