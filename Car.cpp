#include <SFML/Graphics.hpp>
#include "Car.h"

Car::Car(float x, float y, float width, float height, int health) : health(health) {
    if (!texture.loadFromFile("C:\\Users\\Barr Avrahamov\\source\\repos\\SFML_Stuff\\SFML_Stuff\\Car game v4\\Cars\\Car red\\Car red.png")) {
        throw "error";
    }
    car = *(new sf::RectangleShape(sf::Vector2f(width, height)));
    car.setTexture(&texture);
    car.setPosition(x, y);
}

void Car::draw(sf::RenderWindow& window) {
    window.draw(car);
}

void Car::move(int x, int y) {
    car.move(x, y);
}
void Car::setScale(float x, float y) {
    car.setScale(x, y);
}
