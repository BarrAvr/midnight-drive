#pragma once
#include "Obstacle.h"

class Gasoline : public Obstacle
{
private:
    void makeCrashSound() override;
public:
    Gasoline(Score& score);
    std::string type() const override { return "gasoline"; }
};