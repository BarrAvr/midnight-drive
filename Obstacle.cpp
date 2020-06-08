#include <array>
#include <cassert>
#include "Constants.h"
#include <string_view>
#include "Obstacle.h"
#include "Player.h"

Obstacle::Obstacle() : damage_level(10)
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

//// TODO: Use std::unique_ptr instead of raw pointer
//Obstacle* Obstacle::createObstacles(const size_t windowWidth)
//{
//    auto obstacle = new Obstacle();
//    auto& obs = obstacle->getObstacle();
//    obs.setPosition(rand() % static_cast<int>(windowWidth - obs.getSize().x), -100.f);
//
//    return obstacle;
//}

bool Obstacle::checkCollisions(Player player, Obstacle* obs_ptr) {
    return (obs_ptr->getX() + obs_ptr->getWidth() > player.getX() && player.getX() + player.getWidth() > obs_ptr->getX() && (obs_ptr->getY() + obs_ptr->getHeight() > player.getY() && player.getY() + player.getHeight() > obs_ptr->getY()));
}

/*
#include "obstacle.h"

using namespace obs;

Obstacle::Obstacle(float x, float y, float width, float height, int damage_level) : damage_level(damage_level) {
    if (!texture.loadFromFile("C:\\Users\\Barr Avrahamov\\source\\repos\\SFML_Stuff\\SFML_Stuff\\Car game v4\\Construction objects\\Traffic cone.png")) {
        throw "error";
    }
    obstacle = (sf::RectangleShape(sf::Vector2f(width, height)));
    obstacle.setTexture(&texture);
    obstacle.setPosition(x, y);
}

void Obstacle::draw(sf::RenderWindow &window) {
    window.draw(obstacle);
}

void Obstacle::move(int x, int y) {
    obstacle.move(x, y);
}
void Obstacle::setScale(float x, float y) {
    obstacle.setScale(x, y);
}

bool Obstacle::checkCollisions(Car car, Obstacle* obs_ptr) {
    return (obs_ptr->getX() + obs_ptr->getWidth() > car.getX() && car.getX() + car.getWidth() > obs_ptr->getX() && (obs_ptr->getY() + obs_ptr->getHeight() > car.getY() && car.getY() + car.getHeight() > obs_ptr->getY()));
}
*/