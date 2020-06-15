#include <array>
#include <cassert>
#include "Constants.h"
#include <string_view>
#include "Obstacle.h"
#include "Player.h"

namespace cs = constants;




Obstacle::Obstacle(Score& score, int damage_level) : score_(score), damage_level(damage_level)
{
    //do nothing
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