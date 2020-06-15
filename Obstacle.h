#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "Player.h"
#include "Score.h"
#include <SFML/Audio.hpp>

#pragma once

class Obstacle
{
protected:
	sf::Sprite obstacle_;
	sf::Texture texture_;
	Score& score_;
	int damage_level;
	virtual void makeCrashSound() = 0;
	sf::SoundBuffer crashBuffer;
	sf::Sound crashSound;
public:
	explicit Obstacle(Score& score, int damage_level);
	virtual std::string type() const = 0;
	void crashInToCar(Player& player) { player.getHit(Player::Damage::HIT, damage_level); makeCrashSound();};
	sf::Sprite& getObstacle();
	void move(sf::RenderWindow& window, std::vector<Obstacle*>& obstacles, int i, float speedMultiplier);
	void draw(sf::RenderWindow& window);
	const float getX() { return obstacle_.getPosition().x; };
	const float getY() { return obstacle_.getPosition().y; };
	static bool checkCollisions(Player, Obstacle*);
	int getDamage() { return damage_level; }
};