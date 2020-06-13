#include <array>
#include <cassert>
#include "Constants.h"
#include <string_view>
#include "Obstacle.h"

namespace cs = constants;

Obstacle::Obstacle()
{
    const std::string path{constants::PATHS.at(rand() % constants::PATHS.size())};
    assert(texture_.loadFromFile(constants::ResourcePath + path));

    obstacle_.setScale(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(texture_);
}

sf::Sprite& Obstacle::getObstacle()
{
    return obstacle_;
}

void Obstacle::move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i)
{

    obstacle_.move(0.f, constants::obstacleMoveSpeed);
    if (obstacle_.getPosition().y > window.getSize().y)
    {
        obstacles.erase(obstacles.begin() + i);
        score_ += 5;
    }
}

void Obstacle::draw(sf::RenderWindow& window)
{
    window.draw(obstacle_);
}

Obstacle* Obstacle::createObstacles(const size_t windowWidth)
{
    auto obstacle = new Obstacle();
    auto& obs = obstacle->getObstacle();
    obs.setPosition(cs::targetX_[static_cast<int>(rand() % 4)], -50.f);

    return obstacle;
}

