#include <array>
#include <cassert>
#include "Constants.h"
#include <string_view>
#include "Obstacle.h"

Obstacle::Obstacle()
{
    const std::string path{constants::PATHS.at(rand() % constants::PATHS.size())};
    assert(texture_.loadFromFile(constants::ResourcePath + path));

    obstacle_.setSize(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(&texture_);
}

sf::RectangleShape& Obstacle::getObstacle()
{
    return obstacle_;
}

void Obstacle::move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i)
{

    obstacle_.move(0.f, 5.f);
    if (obstacle_.getPosition().y > window.getSize().y)
    {
        obstacles.erase(obstacles.begin() + i);
    }
}

void Obstacle::draw(sf::RenderWindow& window)
{
    window.draw(obstacle_);
}

// TODO: Use std::unique_ptr instead of raw pointer
Obstacle* Obstacle::createObstacles(const size_t windowWidth)
{
    auto obstacle = new Obstacle();
    auto& obs = obstacle->getObstacle();
    obs.setPosition(rand() % static_cast<int>(windowWidth - obs.getSize().x), 0.f);

    return obstacle;
}


