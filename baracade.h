#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Obstacle.h"

using namespace obs;

class Baracade : public Obstacle {
private:
	const std::string BARACADE_CRASH_SOUND_FILE_LOCATION;
	void makeCrashSound(sf::RenderWindow&);
public:
	Baracade();
	Baracade(float x, float y, float width, float height, int damage_level = 50);
	std::string type() const { return "baracade"; };
};