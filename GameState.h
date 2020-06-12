#pragma once

#include "Background.h"
#include "Obstacle.h"
#include "Player.h"
#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameState
{
private:
    sf::Clock obstacleSpawningClock;
    sf::Clock obstacleMovingClock;
    sf::Clock backgroundMovingClock;
    sf::Clock speedUpClock;
    sf::Clock scoreClock;
    int gameSpeed = 1000;
    int score;
    sf::Font font;
    sf::Text health_text, pause_text;
    sf::RenderWindow window_;
    std::vector<Obstacle*> obstacles_;
    Player player_ = Player();
    Background background_ = Background();
    bool backdoorOn = false;
    bool stopSpawning = false;
    int backdoorCount = 0;
    bool gamePaused = false;
    int pauseCount = 0;
    MainMenu menu{};

    void setWindow();
    void spawnObstacles();
    void moveObstacles();
    void drawGame();
    void checkPlayerObstacleCollisions();
    void updateScore();
    void speedUp();
public:
    GameState() {};
    ~GameState() {};    
    void handleEvent(sf::Event& event);
    void runGame();
    void createMenu();
    void startDriving();
    Obstacle* createObstacles(const size_t windowWidth);
};
