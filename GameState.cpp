#include "Constants.h"
#include "GameState.h"
#include "Obstacle.h"

namespace cs = constants;

void GameState::runGame()
{

    this->createMenu();
}

void GameState::createMenu()
{
    MainMenu menu{};

    sf::RenderWindow window(sf::VideoMode(cs::WindowWidth_, cs::WindowHeight_), "Driving Game");
    menu.addMusic();
    bool play = menu.addMenu(window);
    if(play)
    {
        window.close();
        this->startDriving();

    }
}

void GameState::startDriving()
{
    this->setWindow();
    while (window_.isOpen())
    {

        sf::Event event;

        this->handleEvent(event);
        this->spawnObstacles();
        player_.movePlayer();

        window_.clear();

        this->drawGame();

        window_.display();
    }
}

void GameState::setWindow()
{
    sf::VideoMode vm = sf::VideoMode(constants::WindowWidth_, constants::WindowHeight_);
    window_.create(vm, "Midnight Drive");
    window_.setFramerateLimit(constants::frameRate_);
}

void GameState::handleEvent(sf::Event& event)
{
    while (window_.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                window_.close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                Player::Movement playerDirection = Player::Movement::NONE;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    // move car right
                    playerDirection = Player::Movement::RIGHT;

                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    // move car left
                    playerDirection = Player::Movement::LEFT;
                }
                player_.changeLane(playerDirection);
                break;
            }
            default:
                break;
        }
    }
}

void GameState::spawnObstacles()
{
    if (obstacleSpawnTimer_ < 20) {
        obstacleSpawnTimer_++;
    } else {
        auto obstacle = Obstacle::createObstacles(constants::WindowWidth_);
        obstacles_.push_back(obstacle);
        obstacleSpawnTimer_ = 0;
    }

    for (auto i = 0; i < obstacles_.size(); i++)
    {
        auto obs = obstacles_.at(i);
        obs->move(window_, obstacles_, i);
    }
}

void GameState::drawGame()
{
    background_.changeBackground(window_);
    background_.draw(window_);

    for (auto& obs : obstacles_)
    {
        obs->draw(window_);
    }

    player_.draw(window_);
}
