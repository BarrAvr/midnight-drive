#pragma once
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "Obstacle.h"
#include "Player.h"
#include "MainMenu.h"
#include "HealthScore.h"
#include "Score.h"
#include "Scoreboard.h"

class GameState
{
private:
    sf::RenderWindow gameWindow;
    Player gamePlayer = Player(health);
    std::vector<Obstacle*> obstacles;
    Score gameScore = Score();
    Background bg = Background();
    HealthScore health = HealthScore();
    sf::Music music;

    int obstacleSpawnTimer = 0;
    float speedMultiplier = 1.0;
    bool gamePaused = false;
    bool backdoor = false;
    bool stopSpawning = false;
    bool invulnerability = false;

    void spawnObstacles();
    void moveObstacles();
    void drawGame();
    Obstacle* createObstacles(Score& score);
public:
    enum class GameResult
    {
        RAGEQUIT,
        DIED,
    };

    GameResult runGame();
    explicit GameState();
    ~GameState();

    void handleEvent(sf::Event& event);
    Score getFinalScore();
};
