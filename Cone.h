#pragma once
#include "Obstacle.h"

class Cone : public Obstacle
{
private:
    void makeCrashSound() override;
public:
    Cone(Score& score);
    std::string type() const override { return "cone"; }
};