#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"


class Pothole : public Obstacle {
private:
	void makeCrashSound();
public:
	Pothole();
	Pothole(float x, float y, float width, float height, int damage_level = 20);
	std::string type() const { return "pothole"; };
};