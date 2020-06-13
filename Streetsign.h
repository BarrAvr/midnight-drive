#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Obstacle.h"

using namespace obs;

class Streetsign : public Obstacle {
private:
	void makeCrashSound();
public:
	Streetsign();
	Streetsign(float x, float y, float width, float height, int damage_level = 50);
	std::string type() const { return "streetsign"; };
};