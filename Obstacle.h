#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include <SFML/Audio.hpp>

#pragma once
namespace obs {
}

class Obstacle
{
protected:
    sf::RectangleShape obstacle_;
    sf::Texture texture_;
	int damage_level;
	virtual void makeCrashSound() = 0;
	sf::SoundBuffer  crashBuffer;
	sf::Sound crashSound;
public:
    explicit Obstacle();
	virtual std::string type() const = 0;// { return "obstacle"; };//const = 0;
	void crashInToCar(sf::RenderWindow& window, Player& player) { player.setHealth(player.getHealth() - damage_level); makeCrashSound(); };
    sf::RectangleShape& getObstacle();
    void move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i);
    void draw(sf::RenderWindow& window);
	const float getX() { return obstacle_.getPosition().x; };
	const float getY() { return obstacle_.getPosition().y; };
	const float getWidth() { return obstacle_.getSize().x; };
	const float getHeight() { return obstacle_.getSize().y; };
    //static Obstacle* createObstacles(size_t windowWidth);
	static bool checkCollisions(Player, Obstacle*);
	int getDamage() { return damage_level; }
};

/*
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
*/