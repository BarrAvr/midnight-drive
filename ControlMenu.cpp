#include "Constants.h"
#include "ControlMenu.h"

namespace cs = constants;

ControlMenu::ControlMenu() : Screen()
{

    //TODO: Implement file check
    if (!font.loadFromFile(cs::ResourcePath + cs::font))
    {}

    sf::Text temp;
    temp.setFont(font);
    temp.setOutlineColor(sf::Color::White);
    temp.setOutlineThickness(cs::controlOutlineThickness);
    temp.setStyle(sf::Text::Bold);

    for (auto i = 0; i < cs::controlStrings.size(); i++)
    {
        if (i == 0)
        {
            temp.setFillColor(cs::menuFillColor[i]);
        } else {
            temp.setFillColor(sf::Color::Black);
        }
        temp.setCharacterSize(cs::controlCharacterSize[i]);
        temp.setString(cs::controlStrings[i]);
        temp.setPosition(cs::controlPositions[i]);
        menuText.push_back(temp);
    }

    selectedBack = false;
}

void ControlMenu::draw(sf::RenderWindow& window)
{
    sf::Texture texture;

    //TODO: Implement file check
    if (!texture.loadFromFile(cs::ResourcePath + cs::menuBackground))
    {}

    sf::Sprite background(texture);
    background.setScale(cs::menuBgScaleX, cs::menuBgScaleY);
    window.draw(background);

    for (const auto& i : menuText)
    {
        window.draw(i);
    }
}

void ControlMenu::hoverSelected(int selection)
{
    if (selection)
    {
        selectedBack = true;
        menuText[4].setFillColor(cs::onHover.first);
        menuText[4].setOutlineThickness(cs::onHover.second);
    } else
    {
        selectedBack = false;
        menuText[4].setFillColor(cs::offHover.first);
        menuText[4].setOutlineThickness(cs::offHover.second);

    }
}
