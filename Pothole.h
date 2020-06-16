#pragma once
#include "Obstacle.h"

class Pothole : public Obstacle
{
private:
    void makeCrashSound() override;
public:
    Pothole(Score& score);
    std::string type() const override { return "pothole"; }
};