#pragma once

#include "Background.h"
#include "Obstacle.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class GameState
{
private:
    int obstacleSpawnTimer_ = 0;

    sf::RenderWindow window_;
    std::vector<Obstacle*> obstacles_;
    Player player_ = Player();
    Background background_ = Background();

    void setWindow();
    void spawnObstacles();
    void drawGame();

public:
    GameState() = default;
    ~GameState() = default;
    void handleEvent(sf::Event& event);
    void runGame();
};

