#include "GameState.h"
#include "Collision.h"
#include "Constants.h"
#include "Cone.h"
#include "Barricade.h"
#include "Gasoline.h"
#include "Streetsign.h"
#include "Trashcan.h"
#include "Pothole.h"

namespace cs = constants;

GameState::GameResult GameState::runGame()
{
    gameWindow.setVerticalSyncEnabled(true);

    while (gameWindow.isOpen())
    {
        sf::Event event{};

        this->handleEvent(event);
        if (!stopSpawning)
        {
            this->spawnObstacles();
        }
        this->moveObstacles();

        gamePlayer.movePlayer(speedMultiplier);
        gameWindow.clear();

        if (health.getHealth() <= 0)
        {
            return GameState::GameResult::DIED;
        }
        this->drawGame();

        gameWindow.display();
    }

    return GameState::GameResult::RAGEQUIT;
}

GameState::GameState() : gameWindow(sf::VideoMode(cs::WINDOW_WIDTH, cs::WINDOW_HEIGHT), cs::GAME_WINDOW_TITLE)
{
    gameWindow.setFramerateLimit(cs::FRAME_RATE);
    music.openFromFile(cs::RESOURCE_PATH + "background_music.wav");
    music.setVolume(15);
    music.play();
    music.setLoop(true);
}

GameState::~GameState()
{
    gameWindow.close();
    for (auto& obs : obstacles)
    {
        delete obs;
    }
}

void GameState::handleEvent(sf::Event& event)
{
    while (gameWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            gameWindow.close();
            break;
        }
        case sf::Event::KeyPressed:
        {
            Player::Movement playerDirection = Player::Movement::NONE;
            if (!gamePaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))     // Set car to move right
            {
                playerDirection = Player::Movement::RIGHT;
            }
            else if (!gamePaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Set car to move left
            {
                playerDirection = Player::Movement::LEFT;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))       // Turn on/off backdoor
            {
                backdoor = !backdoor;
                if (backdoor)
                {
                    std::cout << "Backdoor is on" << std::endl;
                }
                else
                {
                    std::cout << "Backdoor is off" << std::endl;
                    stopSpawning = false;
                    invulnerability = false;
                }
            }
            else if (backdoor && sf::Keyboard::isKeyPressed(sf::Keyboard::S))   // Turn object spawning on/off
            {
                stopSpawning = !stopSpawning;
                stopSpawning ? std::cout << "Obstacle spawning is turned off" << std::endl : std::cout << "Obstacle spawning is turned on" << std::endl;
            }
            else if (backdoor && sf::Keyboard::isKeyPressed(sf::Keyboard::I))   // Turn Invulnerability on/off
            {
                invulnerability = !invulnerability;
                invulnerability ? std::cout << "Invulnerability is turned on" << std::endl : std::cout << "Invulnerability is turned off" << std::endl;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))       // Turn on/off game pause
            {
                gamePaused = !gamePaused;
                gamePaused ? music.pause() : music.play();
                gamePaused && backdoor ? std::cout << "Game paused" << std::endl : std::cout << "Game resumed" << std::endl;
            }
            gamePlayer.changeLane(playerDirection);
            break;
        }
        default:
            break;
        }
    }
}

void GameState::spawnObstacles()
{
    if (!gamePaused)
    {
        if (obstacleSpawnTimer < 800 / (constants::BASE_BACKGROUND_MOVE_SPEED * speedMultiplier) / 3)
        {
            obstacleSpawnTimer++;
        }
        else
        {
            auto obstacle = createObstacles(gameScore);
            obstacles.push_back(obstacle);
            obstacleSpawnTimer = 0;
        }
    }
}

void GameState::moveObstacles()
{
    if (!gamePaused)
    {
        for (auto i = 0; i < obstacles.size(); i++)
        {
            auto obs = obstacles.at(i);
            obs->move(gameWindow, obstacles, i, speedMultiplier);
        }
        // Based on score, change speedMultipler_ += 0.1
        if (gameScore.getScore() >= 100 && gameScore.getScore() % 100 == 0) {
            if (speedMultiplier < 3.0)
            {
                speedMultiplier += 0.01;
            }
        }
    }
}

void GameState::drawGame()
{
    bg.draw(gameWindow);

    if (!gamePaused)
    {
        bg.changeBackground(gameWindow, speedMultiplier);
    }
    else
    {
        sf::Text pauseText;
        sf::Font font;
        font.loadFromFile(cs::RESOURCE_PATH + cs::FONT);
        pauseText.setFont(font);
        pauseText.setString("Game paused,\npress P to\nresume");
        pauseText.setScale(cs::PAUSE_X_SCALE, cs::PAUSE_Y_SCALE);
        pauseText.setPosition(cs::PAUSE_X, cs::PAUSE_Y);
        pauseText.setCharacterSize(cs::PAUSE_SIZE);
        pauseText.setFillColor(sf::Color::White);
        gameWindow.draw(pauseText);
    }

    for (auto& obs : obstacles)
    {
        obs->draw(gameWindow);
    }

    gamePlayer.draw(gameWindow);

    for (auto i = 0; i < obstacles.size(); i++)
    {
        if (!invulnerability)
        {
            if (Collision::PixelPerfectTest(gamePlayer.getPlayer(), obstacles[i]->getObstacle()))
            {
                if (obstacles[i]->type() == "obstacle")
                {
                    dynamic_cast<Obstacle*>(obstacles[i])->crashInToCar(gamePlayer);
                    if (backdoor)
                        std::cout << "Hit an obstacle! Minus " << obstacles[i]->getDamage() << " damage" << std::endl;
                }
                else if (obstacles[i]->type() == "cone")
                {
                    dynamic_cast<Cone*>(obstacles[i])->crashInToCar(gamePlayer);
                    if (backdoor)
                        std::cout << "Hit a cone! Minus " << obstacles[i]->getDamage() << " damage" << std::endl;
                }
                else if (obstacles[i]->type() == "barricade")
                {
                    dynamic_cast<Barricade*>(obstacles[i])->crashInToCar(gamePlayer);
                    if (backdoor)
                        std::cout << "Hit a barricade! Minus " << obstacles[i]->getDamage() << " damage" << std::endl;
                }
                else if (obstacles[i]->type() == "gasoline")
                {
                    dynamic_cast<Gasoline*>(obstacles[i])->crashInToCar(gamePlayer);
                    if (backdoor)
                        std::cout << "Hit a gasoline! Plus " << -obstacles[i]->getDamage() << " health" << std::endl;
                }
                else if (obstacles[i]->type() == "pothole")
                {
                    dynamic_cast<Pothole*>(obstacles[i])->crashInToCar(gamePlayer);
                    if (backdoor)
                        std::cout << "Hit a pothole! Minus " << obstacles[i]->getDamage() << " health" << std::endl;
                }
                else if (obstacles[i]->type() == "streetsign")
                {
                    dynamic_cast<Streetsign*>(obstacles[i])->crashInToCar(gamePlayer);
                    if (backdoor)
                        std::cout << "Hit a streetsign! Minus " << obstacles[i]->getDamage() << " health" << std::endl;
                }
                else if (obstacles[i]->type() == "trashcan")
                {
                    dynamic_cast<Trashcan*>(obstacles[i])->crashInToCar(gamePlayer);
                    if (backdoor)
                        std::cout << "Hit a trashcan! Minus " << obstacles[i]->getDamage() << " health" << std::endl;
                }
                obstacles.erase(obstacles.begin() + i);
            }
            else
            {
                gamePlayer.getHit(Player::Damage::NOT_HIT);
            }
        }
    }

    health.draw(gameWindow);
    if (!backdoor)
    {
        gameScore.draw(gameWindow);
    }
}

Score GameState::getFinalScore()
{
    return gameScore;
}

Obstacle* GameState::createObstacles(Score& score)
{
    Obstacle* obstacle;

    int odds = rand() % 100 + 1;
    if (odds <= 5)
    {
        obstacle = new Gasoline(score);
        if (backdoor)
            std::cout << "Gasoline obstacle spawned" << std::endl;
    }
    else if (odds <= 5 + 10)
    {
        obstacle = new Barricade(score);
        if (backdoor)
            std::cout << "Barricade obstacle spawned" << std::endl;
    }
    else if (odds <= 5 + 10 + 10)
    {
        obstacle = new Trashcan(score);
        if (backdoor)
            std::cout << "Trashcan obstacle spawned" << std::endl;
    }
    else if (odds <= 5 + 10 + 10 + 5)
    {
        obstacle = new Streetsign(score);
        if (backdoor)
            std::cout << "Streetsign obstacle spawned" << std::endl;
    }
    else if (odds <= 5 + 10 + 10 + 5 + 30)
    {
        obstacle = new Pothole(score);
        if (backdoor)
            std::cout << "Pothole obstacle spawned" << std::endl;
    }
    else
    {
        obstacle = new Cone(score);
        if (backdoor)
            std::cout << "Cone obstacle spawned" << std::endl;
    }

    auto& obs = obstacle->getObstacle();
    int lanePos = static_cast<int>(rand() % 4);
    obs.setPosition(cs::TARGET_X[static_cast<int>(rand() % 4)], -50.f);

    return obstacle;
}