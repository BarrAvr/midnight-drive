#pragma once
#include "Obstacle.h"

class Streetsign : public Obstacle
{
private:
    void makeCrashSound();
public:
    Streetsign(Score& score);
    std::string type() const { return "streetsign"; }
};