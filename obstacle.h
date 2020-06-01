#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Car.h"

namespace obs {
	class Obstacle {
	protected:
		sf::Texture texture;
		sf::RectangleShape obstacle;
		int damage_level;
		virtual void makeCrashSound(sf::RenderWindow&) = 0;
	public:
		Obstacle(float x, float y, float width, float height, int damage_level);
		virtual std::string type() const = 0;
		void crashInToCar(sf::RenderWindow& window, Car& car) { car.setHealth(car.getHealth() - damage_level); makeCrashSound(window); };
		void setX(float x) { obstacle.setPosition(x, obstacle.getPosition().y); };
		void setY(float y) { obstacle.setPosition(obstacle.getPosition().x, y); };
		void move(int x, int y);
		void setScale(float x, float y);
		const float getX() { return obstacle.getPosition().x; };
		const float getY() { return obstacle.getPosition().y; };
		const float getWidth() { return obstacle.getSize().x; };
		const float getHeight() { return obstacle.getSize().y; };
		void draw(sf::RenderWindow&);
		static bool checkCollisions(Car, Obstacle*);
	};
}