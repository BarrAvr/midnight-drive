#pragma once
#include "Screen.h"

class Instructions : public virtual Screen
{
private:
    bool selectedBack = false;
public:
    Instructions();
    ~Instructions() = default;
    void draw(sf::RenderWindow& window) override;
    void hoverSelected(int selection) override;
    bool getSelectedBack() const { return selectedBack; }
};