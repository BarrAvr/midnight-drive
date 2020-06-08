#pragma once
#include <SFML/Graphics.hpp>
#include "obstacle.h"

using namespace obs;

class Gasoline : public Obstacle {
private:
	const std::string GASOLINE_CRASH_SOUND_FILE_LOCATION;
	void makeCrashSound(sf::RenderWindow&);
public:
	Gasoline();
	Gasoline(float x, float y, float width, float height, int damage_level = -10);
	std::string type() const { return "gasoline"; };
};