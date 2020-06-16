#pragma once
#include "Obstacle.h"

class Cone : public Obstacle
{
private:
    void makeCrashSound();
public:
    Cone(Score& score);
    std::string type() const { return "cone"; }
};
