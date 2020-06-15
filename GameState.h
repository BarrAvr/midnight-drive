#pragma once

#include "Background.h"
#include "Obstacle.h"
#include "Player.h"
#include "MainMenu.h"
#include "HealthScore.h"
#include "Score.h"
#include "Scoreboard.h"
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
    Score score_ = Score();
    float speedMultiplier_ = 1.0;
    bool gamePaused = false;
    bool backdoor = false;
    bool stopSpawning = false;
    bool invulnerability = false;
    void spawnObstacles();
    void moveObstacles();
    void drawGame();
    Obstacle* createObstacles(Score& score);
public:
    enum class GameResult {
        RAGEQUIT,
        DIED,
    };

    explicit GameState();
    ~GameState();
    void handleEvent(sf::Event& event);
    Score getFinalScore();
    GameResult runGame();
};
