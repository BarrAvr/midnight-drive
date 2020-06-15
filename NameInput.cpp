#include "NameInput.h"
#include "Constants.h"

namespace cs = constants;

NameInput::NameInput()
{
    //NEED TO IMPLEMENT FILE CHECK HERE!
    if (!font.loadFromFile(cs::ResourcePath + "double_pixel-7.ttf"))
    {
        //bad stuff happens
    }

    sf::Text temp;

    temp.setFont(font);
    temp.setOutlineThickness(3);
    temp.setOutlineColor(sf::Color::White);
    temp.setFillColor(sf::Color::Red);
    temp.setStyle(sf::Text::Bold);
    temp.setCharacterSize(120);
    temp.setString("GAME OVER");
    temp.setPosition(sf::Vector2f(cs::WindowWidth_ * .28, 50));
    line.push_back(temp);

    temp.setOutlineThickness(3);
    temp.setOutlineColor(sf::Color::White);
    temp.setFillColor(sf::Color::Black);
    temp.setStyle(sf::Text::Bold);
    temp.setStyle(sf::Text::Underlined);
    temp.setCharacterSize(80);
    temp.setString("Enter your name:");
    temp.setPosition(sf::Vector2f(cs::WindowWidth_ * .1, cs::WindowHeight_ * .36));
    line.push_back(temp);

    temp.setStyle(sf::Text::Regular);
    temp.setStyle(sf::Text::Bold);
    temp.setString("Continue");
    temp.setPosition(sf::Vector2f(cs::WindowWidth_ * .4, cs::WindowHeight_ * .55));
    line.push_back(temp);

    textbox.setFont(font);
    textbox.setCharacterSize(80);
    textbox.setFillColor(sf::Color::Black);
    textbox.setOutlineThickness(3);
    textbox.setOutlineColor(sf::Color::White);
    textbox.setPosition(sf::Vector2f(cs::WindowWidth_ * .6, cs::WindowHeight_ * .36));

    textbox.setString("_");

    continueSelected = false;
}

void NameInput::inputLogic(int charTyped)
{
    //8 is the delete key, 13 is the enter key
    if (charTyped != 8 && charTyped != 13 && text.str().length() < 7)
    {
        text << static_cast<char>(charTyped);
    }

    else if (charTyped == 8) //enter is pressed
    {
        if (text.str().length() > 0)
            deleteLastChar();
    }

    if (text.str().length() < 7)
        textbox.setString(text.str() + "_");
    else
        textbox.setString(text.str());
}

void NameInput::deleteLastChar()
{
    std::string t = text.str();
    std::string newt;
    for (int i = 0; i < t.length() - 1; i++)
    {
        newt += t[i];
    }

    text.str("");
    text << newt;

    textbox.setString(text.str());
}

void NameInput::typedOn(sf::Event input)
{
    int charTyped = input.text.unicode;

    if (charTyped < 128)
    {
        inputLogic(charTyped);
    }
}


void NameInput::draw(sf::RenderWindow& window)
{
    sf::Texture texture;

    //NEED TO IMPLEMENT FILE CHECK HERE!
    if (!texture.loadFromFile(cs::ResourcePath + "pixel_background2.png"))
    {
        //bad stuff happens
    }

    sf::Sprite background(texture);
    background.setScale(2, 2);
    window.draw(background);

    window.draw(textbox);
    window.draw(line[0]);
    window.draw(line[1]);
    window.draw(line[2]);
}

std::string NameInput::getName()
{
    return text.str();
}

void NameInput::hoverSelected(int selection)
{
    if (selection == 1)
    {
        continueSelected = true;
        line[2].setOutlineThickness(4);
        line[2].setFillColor(sf::Color::Blue);
    } else
    {
        continueSelected = false;
        line[2].setOutlineThickness(3);
        line[2].setFillColor(sf::Color::Black);
    }
}

NameInput::Score NameInput::addScoreToFile(std::ostream& file)
{
    return NameInput::Score();
}
