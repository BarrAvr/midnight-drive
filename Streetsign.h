#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Obstacle.h"


class Streetsign : public Obstacle {
private:
	void makeCrashSound();
public:
	Streetsign(Score& score);
	std::string type() const { return "streetsign"; };
};