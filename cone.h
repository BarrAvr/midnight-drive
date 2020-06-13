#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"


class Cone : public Obstacle {
private:
	void makeCrashSound();
public:
	Cone();
	Cone(float x, float y, float width, float height, int damage_level = 20);
	std::string type() const { return "cone"; };
};