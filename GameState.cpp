#include "Constants.h"
#include "GameState.h"
#include "Obstacle.h"
#include "cone.h"
#include "baracade.h"
#include "gasoline.h"

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
    if (!font.loadFromFile(cs::ResourcePath + cs::font)) {
        
    }
    health_text;
    health_text.setFont(font);

    this->setWindow();
    obstacleClock.restart();
    while (window_.isOpen())
    {
        
        sf::Event event;
        //sf::Clock clock;

        this->handleEvent(event);
        this->spawnObstacles();
        this->moveObstacles();
        player_.movePlayer();
        this->checkPlayerObstacleCollisions();

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
    if (obstacleClock.getElapsedTime().asSeconds() < 1){
        //do nothing
    } else {
        auto obstacle = createObstacles(constants::WindowWidth_);
        obstacles_.push_back(obstacle);
        obstacleClock.restart();
    }
}

void GameState::moveObstacles() {
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

    health_text.setString(std::to_string(player_.getHealth()));
    window_.draw(health_text);
}

void  GameState::checkPlayerObstacleCollisions() {
    //checks to see if there are any collisions and if so crashs the car and deletes the obstacle
    for (auto i = 0; i < obstacles_.size(); i++)
    {
        auto obs = obstacles_.at(i);
        if (Obstacle::checkCollisions(player_, obs)) {
            if (obs->type() == "obstacle") {
                dynamic_cast<Obstacle*>(obs)->crashInToCar(window_, player_);
            }
            else if (obs->type() == "cone") {
                dynamic_cast<Cone*>(obs)->crashInToCar(window_, player_);
            }
            else if (obs->type() == "baracade") {
                dynamic_cast<Baracade*>(obs)->crashInToCar(window_, player_);
            }
            else if (obs->type() == "gasoline") {
                dynamic_cast<Gasoline*>(obs)->crashInToCar(window_, player_);
            }
            delete obs;
            obstacles_.erase(obstacles_.begin() + i--);
        }
    }
}

// TODO: Use std::unique_ptr instead of raw pointer
Obstacle* GameState::createObstacles(const size_t windowWidth)
{
    Obstacle* obstacle;

    int odds = rand() % 100 + 1;
    if (odds <= 10) {
        obstacle = new Gasoline();
    }
    else if (odds <= 40) {
        obstacle = new Baracade();
    }
    else {
        obstacle = new Cone();
    }
    auto& obs = obstacle->getObstacle();

    int lanePos = static_cast<int>(rand() % 4);
    
    //need to fix this so it's not hardcode
    obs.setPosition(constants::targetX_[lanePos] + 10, -100.f);

    return obstacle;
}