#include "MainMenu.h"
#include "Constants.h"
#include "ControlMenu.h"
#include "Screen.h"
#include "NameInput.h"

namespace cs = constants;

MainMenu::MainMenu() : Screen(), window_(sf::VideoMode(cs::WindowWidth_, cs::WindowHeight_), cs::MainMenuTitle)
{
    //TODO: Implement file check
    if (!font.loadFromFile(cs::ResourcePath + cs::font))
    {}

    sf::Text temp;
    temp.setFont(font);
    temp.setStyle(sf::Text::Bold);
    temp.setOutlineColor(sf::Color::White);

    for (auto i = 0; i < cs::menuStrings.size(); i++)
    {
        if (i == 0)
        {
            temp.setCharacterSize(cs::menuTitleSize);
        } else
        {
            temp.setCharacterSize(cs::menuOptionsSize);
        }
        temp.setOutlineThickness(cs::menuOutlineThickness[i]);

        temp.setFillColor(cs::menuFillColor[i]);
        temp.setString(cs::menuStrings[i]);
        temp.setPosition(cs::menuPositions[i]);
        menuText.push_back(temp);
    }

    selectedItemIndex = 1;
}

void MainMenu::draw()
{

    sf::Texture texture;

    //TODO: Implement file check
    if (!texture.loadFromFile(cs::ResourcePath + cs::menuBackground))
    {}

    texture.setSmooth(false);
    sf::Sprite background(texture);
    background.setScale(cs::menuBgScaleX, cs::menuBgScaleY);
    window_.draw(background);

    for (const auto& i : menuText)
    {
        window_.draw(i);
    }
}


void MainMenu::Move()
{
    selectedItemIndex > 1 ? selectedItemIndex-- : selectedItemIndex++;
    menuText[selectedItemIndex].setFillColor(cs::onHover.first);
    menuText[selectedItemIndex].setOutlineThickness(cs::onHover.second);
}

void MainMenu::hoverSelected(int selection)
{
    menuText[selectedItemIndex].setFillColor(cs::offHover.first);
    menuText[selectedItemIndex].setOutlineThickness(cs::offHover.second);

    menuText[selection].setFillColor(cs::onHover.first);
    menuText[selection].setOutlineThickness(cs::onHover.second);
    selectedItemIndex = selection;
}

bool MainMenu::startMenu()
{
    //need to implement file check stuff here
    music.openFromFile(cs::ResourcePath + "background_music.wav");
    music.setVolume(15);

    //need to implement file check stuff here
    carDriving.openFromFile(cs::ResourcePath + "car_start.wav");

    //need to implement file check stuff here
    buffer.loadFromFile(cs::ResourcePath + "button_select.wav");

    button.setBuffer(buffer);

    music.play();

    //control menu
    ControlMenu controls{};

    bool showGame = false, showControls = false;

    while (window_.isOpen())
    {
        while (window_.pollEvent(menuScreen))
        {
            //mouse functionality
            double mouseX = sf::Mouse::getPosition(window_).x;
            double mouseY = sf::Mouse::getPosition(window_).y;

            //for the main menu
            if (!showControls)
            {

                if (menuScreen.type == sf::Event::TextEntered && menuScreen.text.unicode < 128)
                {
                    int index = 0;
                    if (menuScreen.key.code == sf::Keyboard::BackSpace && menuScreen.type == sf::Event::KeyReleased &&
                        index > 0)
                        index--;

                    char buffer[5] = {0, 0, 0, 0, 0};
                    buffer[index] = static_cast<char>(menuScreen.text.unicode);

                    std::cout << buffer;
                }

                //keep track of which menu option is hovered using arrow keys
                if (menuScreen.key.code == sf::Keyboard::Up && menuScreen.type == sf::Event::KeyReleased)
                {
                    button.play();
                    Move();
                }
                if (menuScreen.key.code == sf::Keyboard::Down && menuScreen.type == sf::Event::KeyReleased)
                {
                    button.play();
                    Move();
                }

                //which menu option is selected using enter key
                if (menuScreen.key.code == sf::Keyboard::Return && menuScreen.type == sf::Event::KeyReleased)
                {
                    if (getSelectedItemIndex() == 1) //"entered" play button
                        showGame = true;
                    else if (getSelectedItemIndex() == 2) //"entered" controls button
                        showControls = true;
                    else if (getSelectedItemIndex() == 3) //"entered" scoreboard button
                        window_.close();

                }
                //mouse hovering the play button
                if ((mouseX > window_.getSize().x * (.42) && mouseX < window_.getSize().x * (.55)) &&
                    ((mouseY > window_.getSize().y / 3.8) && (mouseY < window_.getSize().y / 2.7)))
                {
                    if (getSelectedItemIndex() != 1)//prevents music spam
                        button.play();

                    hoverSelected(1);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)//clicks the play button
                        showGame = true;

                }//hovering the controls button
                else if ((mouseX > window_.getSize().x * (.38) && mouseX < window_.getSize().x * (.62)) &&
                         ((mouseY > window_.getSize().y / 2.6) && (mouseY < window_.getSize().y / 2.05)))
                {
                    if (getSelectedItemIndex() != 2) //prevents music spam
                        button.play();

                    hoverSelected(2);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)//clicks the control button
                        showControls = true;

                }//hovering the exit button
                else if ((mouseX > window_.getSize().x * (.43) && mouseX < window_.getSize().x * (.55)) &&
                         ((mouseY > window_.getSize().y / 2.0) && (mouseY < window_.getSize().y / 1.63)))
                {
                    if (getSelectedItemIndex() != 3)//prevents music spam
                        button.play();

                    hoverSelected(3);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)
                    { //clicks the exit button
                        window_.close();
                        return false;
                    }
                }
            }

            //begin the game!
            if (showGame) //Implement the main game here
            {
                return true;
            }
            //for the control menu
            if (showControls)
            {
                if ((mouseX < window_.getSize().x / 6.2) && (mouseY > window_.getSize().y * (.85)))
                {
                    if (!controls.getSelectedBack())
                        button.play();

                    controls.hoverSelected(1);

                    if (menuScreen.type == sf::Event::MouseButtonReleased)
                        showControls = false;

                } else
                {
                    controls.hoverSelected(0);
                }

                if (menuScreen.key.code == sf::Keyboard::Left && menuScreen.type == sf::Event::KeyReleased)
                {
                    showControls = false;
                }

                window_.clear();
                controls.draw(window_);
                window_.display();
            }

            if (!showControls)
            {
                window_.clear();
                draw();
                window_.display();
            }

            //if window is closed
            if (menuScreen.type == sf::Event::Closed)
            {
                window_.close();
                return true;
            }
        }
    }
    return false;
}

MainMenu::~MainMenu()
{
    window_.close();
}
