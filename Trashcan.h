#pragma once
#include "Obstacle.h"

class Trashcan : public Obstacle
{
private:
    void makeCrashSound() override;
public:
    Trashcan(Score& score);
    std::string type() const override { return "trashcan"; }
};