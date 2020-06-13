#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Obstacle.h"

using namespace obs;

class Trashcan : public Obstacle {
private:
	void makeCrashSound();
public:
	Trashcan();
	Trashcan(float x, float y, float width, float height, int damage_level = 30);
	std::string type() const { return "trashcan"; };
};