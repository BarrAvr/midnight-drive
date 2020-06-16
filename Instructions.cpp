#include "FileNotFound.h"
#include "Constants.h"
#include "Instructions.h"

namespace cs = constants;

Instructions::Instructions() : Screen()
{
    std::string fontPath = cs::RESOURCE_PATH + cs::FONT;
    while (!font.loadFromFile(fontPath))
    {
        try { throw FileNotFound("Game Font"); }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            fontPath = e.resolve();
            if (fontPath == "")
                break;
        }
    }

    sf::Text temp;
    temp.setFont(font);
    temp.setOutlineColor(sf::Color::White);
    temp.setOutlineThickness(cs::INSTRUCTION_OUTLINE_THICKNESS);
    temp.setStyle(sf::Text::Bold);

    for (auto i = 0; i < cs::INSTRUCTIONS.size(); i++)
    {
        if (i == 0)
        {
            temp.setFillColor(cs::MENU_FILL_COLOR[i]);
        }
        else
        {
            temp.setFillColor(sf::Color::Black);
        }
        temp.setCharacterSize(cs::INSTRUCTION_CHARACTER_SIZE[i]);
        temp.setString(cs::INSTRUCTIONS[i]);
        temp.setPosition(cs::INSTRUCTION_POSITIONS[i]);
        menuText.push_back(temp);
    }
    selectedBack = false;
}

void Instructions::draw(sf::RenderWindow& window)
{
    sf::Texture texture;

    std::string texturePath = cs::RESOURCE_PATH + cs::MENU_BACKGROUND;
    while (!texture.loadFromFile(texturePath))
    {
        try { throw FileNotFound("Menu Background"); }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            texturePath = e.resolve();
            if (texturePath == "")
                break;
        }
    }

    sf::Sprite background(texture);
    background.setScale(cs::MENU_BG_SCALE_X, cs::MENU_BG_SCALE_Y);
    window.draw(background);

    for (const auto& i : menuText)
    {
        window.draw(i);
    }
}

void Instructions::hoverSelected(int selection)
{
    if (selection)
    {
        selectedBack = true;
        menuText[5].setFillColor(cs::HOVER_ON_COLOR.first);
        menuText[5].setOutlineThickness(cs::HOVER_ON_COLOR.second);
    }
    else
    {
        selectedBack = false;
        menuText[5].setFillColor(cs::HOVER_OFF_COLOR.first);
        menuText[5].setOutlineThickness(cs::HOVER_OFF_COLOR.second);
    }
}
