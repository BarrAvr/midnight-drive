#include "Constants.h"
#include "GameState.h"
#include "Obstacle.h"
#include "Collision.h"

namespace cs = constants;

bool gamePaused = false;
bool backdoor = false;
int pauseCount = 0;
int backdoorCount = 0;

GameState::GameResult GameState::runGame()
{
    window_.setVerticalSyncEnabled(true);

    while (window_.isOpen())
    {
        sf::Event event{};

        this->handleEvent(event);

        this->spawnObstacles();

        player_.movePlayer(speedMultiplier_);
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
    window_.setFramerateLimit(cs::frameRate_);
    music.openFromFile(cs::ResourcePath + "background_music.wav");
    music.setVolume(15);
    music.play();
    music.setLoop(true);
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
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) // Turn on/off backdoor
                {
                    backdoorCount++;
                    if (backdoorCount % 2 != 0)
                    {
                        backdoor = true;
                        std::cout << "Backdoor is on" << std::endl;
                    }
                    else
                    {
                        backdoor = false;
                        std::cout << "Backdoor is off" << std::endl;
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) // Turn on/off pause
                {
                    pauseCount++;
                    if (pauseCount % 2 != 0)
                    {
                        gamePaused = true;
                        if (backdoor)
                            std::cout << "Game paused" << std::endl;
                        music.pause();
                    }
                    else
                    {
                        gamePaused = false;
                        if (backdoor)
                            std::cout << "Game resumed" << std::endl;
                        music.play();
                    }
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
    if (!gamePaused)
    {
        if (obstacleSpawnTimer_ < 30)
        {
            obstacleSpawnTimer_++;
        } else
        {
            auto obstacle = Obstacle::createObstacles(score_);
            obstacles_.push_back(obstacle);
            obstacleSpawnTimer_ = 0;
        }

        for (auto i = 0; i < obstacles_.size(); i++)
        {
            auto obs = obstacles_.at(i);
            obs->move(window_, obstacles_, i, speedMultiplier_);
        }
        // Based on score, change speedMultipler_ += 0.1
        if (score_.getScore() >= 100 && score_.getScore() % 100 == 0) {
            if (speedMultiplier_ < 3.0)
            {
                speedMultiplier_ += 0.01;
            }
        }
    }
}

void GameState::drawGame()
{
    background_.draw(window_);

    if (!gamePaused)
    {
        background_.changeBackground(window_, speedMultiplier_);
    } else
    {
        sf::Text pauseText;
        sf::Font font;
        font.loadFromFile(cs::ResourcePath + cs::font);
        pauseText.setFont(font);
        pauseText.setString("Game paused,\npress P to\nresume");
        pauseText.setScale(cs::pauseXscale, cs::pauseYscale);
        pauseText.setPosition(cs::pauseX, cs::pauseY);
        pauseText.setCharacterSize(cs::pauseSize);
        pauseText.setFillColor(sf::Color::White);
        window_.draw(pauseText);
    }

    for (auto& obs : obstacles_)
    {
        obs->draw(window_);
    }

    player_.draw(window_);

    for (auto i = 0; i < obstacles_.size(); i++)
    {
        if (!backdoor)
        {
            if (Collision::PixelPerfectTest(player_.getPlayer(), obstacles_[i]->getObstacle()))
            {
                player_.getHit(Player::Damage::HIT);
                obstacles_.erase(obstacles_.begin() + i);
            } else
            {
                player_.getHit(Player::Damage::NOT_HIT);
            }
        }
    }

    health_.draw(window_);
    if (!backdoor)
    {
        score_.draw(window_);
    }
}

GameState::~GameState()
{
    window_.close();

    for (auto& obs : obstacles_)
    {
        delete obs;
    }
}

Score GameState::getFinalScore()
{
    return score_;
}
