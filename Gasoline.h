#pragma once
#include "Obstacle.h"

class Gasoline : public Obstacle
{
private:
    void makeCrashSound();
public:
    Gasoline(Score& score);
    std::string type() const { return "gasoline"; }
};
