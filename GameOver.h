#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Scoreboard.h"

class GameOver : public virtual Screen
{
private:
    bool selectedExit = false;
    std::vector<sf::Text> scoresLine;
    std::vector<sf::Text> line;
    sf::Event menuScreen{};
    sf::Sound button;
    sf::RenderWindow window_;
    Scoreboard scoreboard;
    Score newScore_;

public:
    GameOver() = default;

    explicit GameOver(const Score& newScore);

    ~GameOver();

    void draw(sf::RenderWindow& window) override;

    void hoverSelected(int selection) override;

    bool getSelectedExit() const
    { return selectedExit; }

    void addScoresToScreen();

    void startGameOver();


};
