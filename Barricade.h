#pragma once
#include "Obstacle.h"

class Barricade : public Obstacle
{
private:
    void makeCrashSound() override;
public:
    Barricade(Score& score);
    std::string type() const override { return "barricade"; }
};