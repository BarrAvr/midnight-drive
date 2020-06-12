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
    //MainMenu menu{};
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
    //health_text;
    health_text.setFont(font);

    this->setWindow();
    score = 0;
    obstacleSpawningClock.restart();
    scoreClock.restart();
    obstacleMovingClock.restart();
    backgroundMovingClock.restart();
    speedUpClock.restart();
    while (window_.isOpen())
    {
        
        sf::Event event;

        this->handleEvent(event);
        if(!gamePaused) {
            if (player_.getHealth() <= 0) {
                //need to do a game over screen, for now the game is just paused
                gamePaused = true;
            }
            if (!stopSpawning) {
                this->spawnObstacles();
            }
            this->moveObstacles();
            player_.movePlayer(backdoorOn);
            this->checkPlayerObstacleCollisions();
            this->updateScore();
            this->speedUp();

            menu.playMusic();

            window_.clear();
            this->drawGame();
            window_.display();
        } else {
            menu.pauseMusic();
            pause_text.setFont(font);
            pause_text.setString("Game paused,\npress P to\nresume");
            pause_text.setScale(2.0f, 2.0f);
            pause_text.setPosition(10.f, 150.0f);
            this->drawGame();
            window_.display();
        }
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
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) // Turn on/off backdoor
                {
                    backdoorCount++;
                    if(backdoorCount % 2 != 0) {
                        backdoorOn = true;
                        std::cout << "Backdoor is on" << std::endl;
                    } else {
                        backdoorOn = false;
                        stopSpawning = false;
                        std::cout << "Backdoor is off" << std::endl;
                    }
                }
                else if (backdoorOn && sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                    stopSpawning = !stopSpawning;
                    stopSpawning ? std::cout << "Obstacle spawning is turned off" << std::endl : std::cout << "Obstacle spawning is turned on" << std::endl;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) // Turn on/off backdoor
                {
                    pauseCount++;
                    if(pauseCount % 2 != 0) {
                        gamePaused = true;
                        if(backdoorOn)
                            std::cout << "Game paused" << std::endl;
                    } else {
                        gamePaused = false;
                        if(backdoorOn)
                            std::cout << "Game resumed" << std::endl;
                        scoreClock.restart();
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
    if (obstacleSpawningClock.getElapsedTime().asMilliseconds() >= gameSpeed){
        auto obstacle = createObstacles(constants::WindowWidth_);
        obstacles_.push_back(obstacle);
        obstacleSpawningClock.restart();
    }
}

void GameState::moveObstacles() {
    if (obstacleMovingClock.getElapsedTime().asMilliseconds() >= 1.0 * gameSpeed / 50) {
        for (auto i = 0; i < obstacles_.size(); i++)
        {
            auto obs = obstacles_.at(i);
            obs->move(window_, obstacles_, i);
        }
        obstacleMovingClock.restart();
    }
}

void GameState::drawGame()
{
    if (!gamePaused) {
        if (backgroundMovingClock.getElapsedTime().asMilliseconds() >= 1.0 * gameSpeed / 50) {
            background_.changeBackground(window_);
            backgroundMovingClock.restart();
        }
    }
    background_.draw(window_);

    for (auto& obs : obstacles_)
    {
        obs->draw(window_);
    }

    player_.draw(window_);

    health_text.setString("Health: " + std::to_string(player_.getHealth()));
    health_text.setScale(2.0f, 2.0f);
    health_text.setPosition(10.f, 5.0f);
    window_.draw(health_text);

    if(gamePaused)
        window_.draw(pause_text);

}

void  GameState::checkPlayerObstacleCollisions() {
    //checks to see if there are any collisions and if so crashs the car and deletes the obstacle
    for (auto i = 0; i < obstacles_.size(); i++)
    {
        auto obs = obstacles_.at(i);
        if (Obstacle::checkCollisions(player_, obs)) {
            if (obs->type() == "obstacle") {
                dynamic_cast<Obstacle*>(obs)->crashInToCar(window_, player_);
                if(backdoorOn)
                    std::cout << "Hit an obstacle! Minus " << obs->getDamage() << " damage" << std::endl;
            }
            else if (obs->type() == "cone") {
                dynamic_cast<Cone*>(obs)->crashInToCar(window_, player_);
                if(backdoorOn)
                    std::cout << "Hit a cone! Minus " << obs->getDamage() << " damage" << std::endl;
            }
            else if (obs->type() == "baracade") {
                dynamic_cast<Baracade*>(obs)->crashInToCar(window_, player_);
                if(backdoorOn)
                    std::cout << "Hit a baracade! Minus " << obs->getDamage() << " damage" << std::endl;
            }
            else if (obs->type() == "gasoline") {
                dynamic_cast<Gasoline*>(obs)->crashInToCar(window_, player_);
                if(backdoorOn)
                    std::cout << "Hit a gasoline! Plus " << -obs->getDamage() << " health" << std::endl;
            }
            //delete obs;
            obs = nullptr;
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
        /*
        if(backdoorOn)
            std::cout << "Gasoline obstacle" << std::endl;
        */
    }
    else if (odds <= 40) {
        obstacle = new Baracade();
        /*
        if(backdoorOn)
            std::cout << "Baracade obstacle" << std::endl;
        */
    }
    else {
        obstacle = new Cone();
        /*
        if(backdoorOn)
            std::cout << "Cone obstacle" << std::endl;
        */
    }
    auto& obs = obstacle->getObstacle();

    int lanePos = static_cast<int>(rand() % 4);
    
    //need to fix this so it's not hardcode
    obs.setPosition(constants::targetX_[lanePos] + 10, -100.f);

    return obstacle;
}

void GameState::updateScore() {
    if (scoreClock.getElapsedTime().asSeconds() >= 0.5) {
        score += 3;
        scoreClock.restart();
        if (backdoorOn)
            std::cout << "Player score: " << score << std::endl;
    }
}

void GameState::speedUp() {
    if (speedUpClock.getElapsedTime().asSeconds() >= 0.1 / 2) {
        if (gameSpeed > 1) {
            gameSpeed -= 1;
            if (backdoorOn) {
                if (gameSpeed % 10 == 0 || gameSpeed == 1) {
                    std::cout << "Game Speed: " << gameSpeed << std::endl;
                }
            }
        }
        speedUpClock.restart();
    }
}