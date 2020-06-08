#pragma once

#include "Screen.h"

class ControlMenu : public virtual Screen
{
    bool selectedBack = false;
public:
    ControlMenu();
    ~ControlMenu() = default;

    void draw(sf::RenderWindow& window) override;
    void hoverSelected(int selection) override;
    bool getSelectedBack() const { return selectedBack; }
};