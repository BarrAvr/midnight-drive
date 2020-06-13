#pragma once

#include "Background.h"
#include "Obstacle.h"
#include "Player.h"
#include "MainMenu.h"
#include "HealthScore.h"
#include <SFML/Graphics.hpp>

class GameState
{
private:
    int obstacleSpawnTimer_ = 0;
    sf::Music music;
    sf::RenderWindow window_;
    std::vector<Obstacle*> obstacles_;
    HealthScore health_ = HealthScore();
    Player player_ = Player(health_);
    Background background_ = Background();

    void spawnObstacles();
    void drawGame();

public:
    enum class GameResult {
        RAGEQUIT,
        DIED,
    };

    explicit GameState();
    ~GameState();
    void handleEvent(sf::Event& event);
    GameResult runGame();
};
