#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Obstacle.h"


class Baracade : public Obstacle {
private:
	void makeCrashSound();
public:
	Baracade(Score& score);
	std::string type() const { return "baracade"; };
};