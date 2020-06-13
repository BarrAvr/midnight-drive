#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Obstacle.h"

using namespace obs;

class Baracade : public Obstacle {
private:
	void makeCrashSound();
public:
	Baracade();
	Baracade(float x, float y, float width, float height, int damage_level = 50);
	std::string type() const { return "baracade"; };
};