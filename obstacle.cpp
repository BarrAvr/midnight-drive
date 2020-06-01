#include <SFML/Graphics.hpp>
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
