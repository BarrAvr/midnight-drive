#pragma once
#include "Obstacle.h"

class Pothole : public Obstacle
{
private:
    void makeCrashSound();
public:
    Pothole(Score& score);
    std::string type() const { return "pothole"; }
};