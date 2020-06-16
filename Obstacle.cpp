#include <array>
#include "Constants.h"
#include "Obstacle.h"
#include "Drawable.h"

namespace cs = constants;

Obstacle::Obstacle(Score& score, int damage_level) : score(score), damageLevel(damage_level)
{}

void Obstacle::move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i, float speedMultiplier)
{
    obstacle.move(0.f, cs::BASE_OBSTACLE_MOVE_SPEED * speedMultiplier);
    if (obstacle.getPosition().y > window.getSize().y)
    {
        obstacles.erase(obstacles.begin() + i);
        score.addToScore();
    }    
}

void Obstacle::draw(sf::RenderWindow& window)
{
    window.draw(obstacle);
}