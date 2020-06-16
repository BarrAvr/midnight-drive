#pragma once
#include "Screen.h"
#include <sstream>
#include <fstream>

class NameInput : public virtual Screen
{
private:
    bool continueSelected{};
    sf::Text textbox;
    std::ostringstream text;
    std::vector<sf::Text> line;
    sf::Sprite background;
    sf::Texture texture;

public:
    NameInput();
    using Score = std::pair<int, std::string>;

    void inputLogic(int charTyped);
    void deleteLastChar();
    void typedOn(sf::Event input);
    void draw(sf::RenderWindow& window) override;
    void hoverSelected(int selection) override;
    std::string getName();

    bool getContinueSelected() const
    { return continueSelected; }
};

