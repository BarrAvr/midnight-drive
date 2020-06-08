#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Obstacle.h"

//using namespace obs;

class Cone : public Obstacle {
private:
	static const std::string CONE_CRASH_SOUND_FILE_LOCATION;
	void makeCrashSound(sf::RenderWindow&);
public:
	Cone();
	Cone(float x, float y, float width, float height, int damage_level = 20);
	std::string type() const { return "cone"; };
};