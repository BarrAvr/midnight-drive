#pragma once
#include "Obstacle.h"

class Trashcan : public Obstacle
{
private:
    void makeCrashSound();
public:
    Trashcan(Score& score);
    std::string type() const { return "trashcan"; }
};