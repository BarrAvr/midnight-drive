#include "Constants.h"
#include "GameState.h"
#include "Obstacle.h"
#include "Collision.h"
#include "cone.h"
#include "baracade.h"
#include "gasoline.h"
#include "Streetsign.h"
#include "Trashcan.h"
#include "Pothole.h"

namespace cs = constants;

GameState::GameResult GameState::runGame()
{
    window_.setVerticalSyncEnabled(true);

    while (window_.isOpen())
    {

        sf::Event event{};

        this->handleEvent(event);
        if (!stopSpawning) {
            this->spawnObstacles();
        }
        this->moveObstacles();

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
                if (!gamePaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    // move car right
                    playerDirection = Player::Movement::RIGHT;

                } else if (!gamePaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    // move car left
                    playerDirection = Player::Movement::LEFT;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) // Turn on/off backdoor
                {
                    backdoor = !backdoor;
                    if (backdoor) 
                    {
                        std::cout << "Backdoor is on" << std::endl;
                    }
                    else 
                    {
                        std::cout << "Backdoor is on" << std::endl;
                        stopSpawning = false;
                        invulnerability = false;
                    }
                }
                else if (backdoor && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
                {
                    stopSpawning = !stopSpawning;
                    stopSpawning ? std::cout << "Obstacle spawning is turned off" << std::endl : std::cout << "Obstacle spawning is turned on" << std::endl;
                }
                else if (backdoor && sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                {
                    invulnerability = !invulnerability;
                    invulnerability ? std::cout << "Invulnerability is turned on" << std::endl : std::cout << "Invulnerability is turned off" << std::endl;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) // Turn on/off pause
                {
                    gamePaused = !gamePaused;
                    gamePaused ? music.pause() : music.play();
                    gamePaused && backdoor ? std::cout << "Game paused" << std::endl : std::cout << "Game resumed" << std::endl;

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
        if (obstacleSpawnTimer_ < 800 / (constants::baseBackgroundMoveSpeed * speedMultiplier_) / 3)
        {
            obstacleSpawnTimer_++;
        } else
        {
            auto obstacle = createObstacles(score_);
            obstacles_.push_back(obstacle);
            obstacleSpawnTimer_ = 0;
        }
    }
}

void GameState::moveObstacles() {
    if (!gamePaused)
    {
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
        if (!invulnerability)
        {
            if (Collision::PixelPerfectTest(player_.getPlayer(), obstacles_[i]->getObstacle()))
            {
                if (obstacles_[i]->type() == "obstacle") {
                    dynamic_cast<Obstacle*>(obstacles_[i])->crashInToCar(player_);
                    if (backdoor)
                        std::cout << "Hit an obstacle! Minus " << obstacles_[i]->getDamage() << " damage" << std::endl;
                }
                else if (obstacles_[i]->type() == "cone") {
                    dynamic_cast<Cone*>(obstacles_[i])->crashInToCar(player_);
                    if (backdoor)
                        std::cout << "Hit a cone! Minus " << obstacles_[i]->getDamage() << " damage" << std::endl;
                }
                else if (obstacles_[i]->type() == "baracade") {
                    dynamic_cast<Baracade*>(obstacles_[i])->crashInToCar(player_);
                    if (backdoor)
                        std::cout << "Hit a baracade! Minus " << obstacles_[i]->getDamage() << " damage" << std::endl;
                }
                else if (obstacles_[i]->type() == "gasoline") {
                    dynamic_cast<Gasoline*>(obstacles_[i])->crashInToCar(player_);
                    if (backdoor)
                        std::cout << "Hit a gasoline! Plus " << -obstacles_[i]->getDamage() << " health" << std::endl;
                }
                else if (obstacles_[i]->type() == "pothole") {
                    dynamic_cast<Pothole*>(obstacles_[i])->crashInToCar(player_);
                    if (backdoor)
                        std::cout << "Hit a pothole! Minus " << obstacles_[i]->getDamage() << " health" << std::endl;
                }
                else if (obstacles_[i]->type() == "streetsign") {
                    dynamic_cast<Streetsign*>(obstacles_[i])->crashInToCar(player_);
                    if (backdoor)
                        std::cout << "Hit a streetsign! Minus " << obstacles_[i]->getDamage() << " health" << std::endl;
                }
                else if (obstacles_[i]->type() == "trashcan") {
                    dynamic_cast<Trashcan*>(obstacles_[i])->crashInToCar(player_);
                    if (backdoor)
                        std::cout << "Hit a trashcan! Minus " << obstacles_[i]->getDamage() << " health" << std::endl;
                }
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
Obstacle* GameState::createObstacles(Score& score)
{
    Obstacle* obstacle;

    int odds = rand() % 100 + 1;
    if (odds <= 5) 
    {
        obstacle = new Gasoline(score);
        if(backdoor) std::cout << "Gasoline obstacle spawned" << std::endl;
    }
    else if (odds <= 5 + 10) 
    {
        obstacle = new Baracade(score);
        if (backdoor) std::cout << "Baracade obstacle spawned" << std::endl;
    }
    else if (odds <= 5 + 10 + 10) 
    {
        obstacle = new Trashcan(score);
        if (backdoor) std::cout << "Trashcan obstacle spawned" << std::endl;
    }
    else if (odds <= 5 + 10 + 10 + 5) 
    {
        obstacle = new Streetsign(score);
        if (backdoor) std::cout << "Streetsign obstacle spawned" << std::endl;
    }
    else if (odds <= 5 + 10 + 10 + 5 + 30) 
    {
        obstacle = new Pothole(score);
        if (backdoor) std::cout << "Pothole obstacle spawned" << std::endl;
    }
    else 
    {
        obstacle = new Cone(score);
        if (backdoor) std::cout << "Cone obstacle spawned" << std::endl;
    }
    auto& obs = obstacle->getObstacle();

    int lanePos = static_cast<int>(rand() % 4);

    obs.setPosition(cs::targetX_[static_cast<int>(rand() % 4)], -50.f);


    return obstacle;
}