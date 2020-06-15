#include <array>
#include <cassert>
#include "Constants.h"
#include <string_view>
#include "Obstacle.h"

namespace cs = constants;

Obstacle::Obstacle(Score& score) : score_(score)
{
    const std::string path{cs::PATHS.at(rand() % cs::PATHS.size())};
    assert(texture_.loadFromFile(cs::ResourcePath + path));

    obstacle_.setScale(sf::Vector2f(cs::obstacleSize, cs::obstacleSize));
    obstacle_.setTexture(texture_);
}

sf::Sprite& Obstacle::getObstacle()
{
    return obstacle_;
}

void Obstacle::move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i, float speedMultiplier)
{
    obstacle_.move(0.f, cs::baseObstacleMoveSpeed * speedMultiplier);
    if (obstacle_.getPosition().y > window.getSize().y)
    {
        obstacles.erase(obstacles.begin() + i);
        score_.addToScore();
    }
}

void Obstacle::draw(sf::RenderWindow& window)
{
    window.draw(obstacle_);
}

Obstacle* Obstacle::createObstacles(Score& score)
{
    auto obstacle = new Obstacle(score);
    auto& obs = obstacle->getObstacle();
    obs.setPosition(cs::targetX_[static_cast<int>(rand() % 4)], -50.f);

    return obstacle;
}

