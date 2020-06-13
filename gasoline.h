#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"

using namespace obs;

class Gasoline : public Obstacle {
private:
	void makeCrashSound();
public:
	Gasoline();
	Gasoline(float x, float y, float width, float height, int damage_level = -10);
	std::string type() const { return "gasoline"; };
};