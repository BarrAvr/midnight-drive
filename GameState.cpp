#include "Constants.h"
#include "GameState.h"
#include "Obstacle.h"
#include "Collision.h"

namespace cs = constants;

GameState::GameResult GameState::runGame()
{
    while (window_.isOpen())
    {

        sf::Event event{};

        this->handleEvent(event);
        this->spawnObstacles();
        player_.movePlayer();
        window_.clear();

        if (health_.getHealth() <= 0)
        {
            return GameState::GameResult::DIED;
        }
        this->drawGame();

        window_.display();
    }
    return GameState::GameResult::RAGEQUIT;
}

GameState::GameState() : window_(sf::VideoMode(cs::WindowWidth_, cs::WindowHeight_), cs::GameWindowTitle)
{
    window_.setFramerateLimit(constants::frameRate_);
    music.openFromFile(cs::ResourcePath + "background_music.wav");
    music.setVolume(15);
    music.play();
}

void GameState::handleEvent(sf::Event& event)
{
    while (window_.pollEvent(event))
    {
        switch (event.type)
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
    if (obstacleSpawnTimer_ < 30)
    {
        obstacleSpawnTimer_++;
    } else
    {
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

    for (auto i = 0; i < obstacles_.size(); i++)
    {
        if (Collision::PixelPerfectTest(player_.getPlayer(), obstacles_[i]->getObstacle()))
        {
            player_.getHit(Player::Damage::HIT);
            obstacles_.erase(obstacles_.begin() + i);
        } else {
            player_.getHit(Player::Damage::NOT_HIT);
        }
    }

    health_.draw(window_);
}

GameState::~GameState()
{
    window_.close();

    for (auto& obs : obstacles_)
    {
        delete obs;
    }
}
