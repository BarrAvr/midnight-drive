#pragma once
#include <SFML/Graphics.hpp>

class Car {
private:
	sf::Texture texture;
	sf::RectangleShape car;
	int health;
public:
	Car(float x, float y, float width, float height, int health = 100);
	void setX(float x) { car.setPosition(x, car.getPosition().y); };
	void setY(float y) { car.setPosition(car.getPosition().x, y); };
	void move(int x, int y);
	void setScale(float x, float y);
	void setHealth(int newHealth) { health = newHealth; };
	int getHealth() { return health; };
	const float getX() { return car.getPosition().x; };
	const float getY() { return car.getPosition().y; };
	const float getWidth() { return car.getSize().x; };
	const float getHeight() { return car.getSize().y; };
	void draw(sf::RenderWindow&);
};