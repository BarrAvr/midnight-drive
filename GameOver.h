#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Scoreboard.h"

class GameOver : public virtual Screen
{
private:
    bool selectedExit;
    std::vector<sf::Text> scoresLine;
    std::vector<sf::Text> line;
    sf::Event menuScreen{};
    sf::Sound button;
    sf::RenderWindow window_;
public:
    GameOver();

    ~GameOver();

    void draw(sf::RenderWindow& window) override;

    void hoverSelected(int selection) override;

    bool getSelectedExit() const
    { return selectedExit; }

    void addScoresToScreen(Scoreboard& score);

    void startGameOver();
};
