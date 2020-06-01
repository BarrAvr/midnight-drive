#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"
//#include "GameState.h"

class MainMenu
{
private:
    //sf::RenderWindow window;
    sf::Event menuScreen;
    sf::Music music, carDriving;
    sf::SoundBuffer buffer;
    sf::Sound button;
    //Menu menu;
    //Control controls;
    //bool playMenu, controlMenu;
public:
    MainMenu(){};
    ~MainMenu() = default;
    void addMusic();
    bool addMenu(sf::RenderWindow& window);
    //void draw(sf::RenderWindow& window);
};
