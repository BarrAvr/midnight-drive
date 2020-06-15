#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"


class Cone : public Obstacle {
private:
	void makeCrashSound();
public:
	Cone(Score& score);
	std::string type() const { return "cone"; };
};