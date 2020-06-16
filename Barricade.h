#pragma once
#include "Obstacle.h"

class Barricade : public Obstacle
{
private:
    void makeCrashSound();
public:
    Barricade(Score& score);
    std::string type() const { return "barricade"; }
};