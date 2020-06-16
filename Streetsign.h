#pragma once
#include "Obstacle.h"

class Streetsign : public Obstacle
{
private:
    void makeCrashSound() override;
public:
    Streetsign(Score& score);
    std::string type() const override { return "streetsign"; }
};