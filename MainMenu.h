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
public:
    MainMenu();
    ~MainMenu() = default;
    void addMusic();
    void pauseMusic();
    void playMusic();
    bool addMenu(sf::RenderWindow& window);

    void draw(sf::RenderWindow& window) override;
    void Move();
    void hoverSelected(int selection) override;

    int getSelectedItemIndex() const { return selectedItemIndex; }
};
