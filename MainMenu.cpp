#include "MainMenu.h"
#include "Constants.h"
#include "ControlMenu.h"
#include "Screen.h"

namespace cs = constants;

MainMenu::MainMenu() : Screen()
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
    /*
    //need to implement file check stuff here
    music.openFromFile(cs::ResourcePath + "background_music.wav");

    //need to implement file check stuff here
    //carDriving.openFromFile(cs::ResourcePath + "car_start.wav");

    //need to implement file check stuff here
    buffer.loadFromFile(cs::ResourcePath + "button_select.wav");

    button.setBuffer(buffer);

    music.play();
    */
    selectedItemIndex = 1;
}

void MainMenu::draw(sf::RenderWindow& window)
{

    sf::Texture texture;

    //TODO: Implement file check
    if (!texture.loadFromFile(cs::ResourcePath + cs::menuBackground))
    {}

    texture.setSmooth(false);
    sf::Sprite background(texture);
    background.setScale(cs::menuBgScaleX, cs::menuBgScaleY);
    window.draw(background);

    for (const auto& i : menuText)
    {
        window.draw(i);
    }
}

void MainMenu::addMusic()
{

    //need to implement file check stuff here
    music.openFromFile(cs::ResourcePath + "background_music.wav");

    //need to implement file check stuff here
    //carDriving.openFromFile(cs::ResourcePath + "car_start.wav");

    //need to implement file check stuff here
    buffer.loadFromFile(cs::ResourcePath + "button_select.wav");

    button.setBuffer(buffer);
    music.play();
}
void MainMenu::playMusic()
{
    if(music.getStatus() != sf::Music::Playing)
        music.play();
}

void MainMenu::pauseMusic()
{
    music.pause();
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

bool MainMenu::addMenu(sf::RenderWindow& window)
{
    //control menu
    ControlMenu controls{};

    bool showGame = false, showControls = false;

    while (window.isOpen())
    {
        while (window.pollEvent(menuScreen))
        {
            //mouse functionality
            double mouseX = sf::Mouse::getPosition(window).x;
            double mouseY = sf::Mouse::getPosition(window).y;


            //for the main menu
            if (!showControls)
            {
                //keep track of which menu option is hovered using arrow keys
                if(menuScreen.type == sf::Event::KeyPressed)
                {
                    if (menuScreen.key.code == sf::Keyboard::Up || menuScreen.key.code == sf::Keyboard::Down)
                    {
                        button.play();
                        Move();
                    }
                }

                //which menu option is selected using enter key
                if (menuScreen.key.code == sf::Keyboard::Return && menuScreen.type == sf::Event::KeyReleased)
                {
                    if (getSelectedItemIndex() == 1) //"entered" play button
                        showGame = true;
                    else if (getSelectedItemIndex() == 2) //"entered" controls button
                        showControls = true;
                    else if (getSelectedItemIndex() == 3) //"entered" scoreboard button
                        window.close();
                        //TODO: Show scoreboard
                        //showScoreboard = true
                    else if (getSelectedItemIndex() == 4) //"entered" exit button
                        window.close();

                }
                //mouse hovering the play button
                if ((mouseX > window.getSize().x * (.42) && mouseX < window.getSize().x * (.55)) &&
                    ((mouseY > window.getSize().y / 3.8) && (mouseY < window.getSize().y / 2.7)))
                {
                    if (getSelectedItemIndex() != 1)//prevents music spam
                        button.play();

                    hoverSelected(1);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)//clicks the play button
                        showGame = true;

                }//hovering the controls button
                else if ((mouseX > window.getSize().x * (.38) && mouseX < window.getSize().x * (.62)) &&
                         ((mouseY > window.getSize().y / 2.6) && (mouseY < window.getSize().y / 2.05)))
                {
                    if (getSelectedItemIndex() != 2) //prevents music spam
                        button.play();

                    hoverSelected(2);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)//clicks the control button
                        showControls = true;

                }//hovering the scoreboard button
                else if ((mouseX > window.getSize().x * (.43) && mouseX < window.getSize().x * (.60)) &&
                         ((mouseY > window.getSize().y / 2.0) && (mouseY < window.getSize().y / 1.63)))
                {
                        std::cout << "SCOREBOARD" << std::endl;
                        if (getSelectedItemIndex() != 3)//prevents music spam
                            button.play();

                        hoverSelected(3);
                        if (menuScreen.type == sf::Event::MouseButtonReleased)
                        { //clicks the scoreboard button
                           //set scoreboard to show
                           window.close();
                        }
                }//hovering the exit button
                else if ((mouseX > window.getSize().x * (.43) && mouseX < window.getSize().x * (.55)) &&
                         ((mouseY > window.getSize().y / 1.9) && (mouseY < window.getSize().y / 1.2)))
                {
                    std::cout << "HERE" << std::endl;
                    if (getSelectedItemIndex() != 4)//prevents music spam
                        button.play();

                    hoverSelected(4);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)
                    { //clicks the exit button
                        window.close();
                        return false;
                    }
                }
            }

            //begin the game!
            if (showGame) //Implement the main game here
            {
                std::cout << "The game has begun!" << std::endl;
                return true;
            }

            //for the control menu
            if (showControls)
            {
                if ((mouseX < window.getSize().x / 6.2) && (mouseY > window.getSize().y * (.85)))
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

                window.clear();
                controls.draw(window);
                window.display();

            }

            if (!showControls)
            {
                window.clear();
                draw(window);
                window.display();
            }

            //if window is closed
            if (menuScreen.type == sf::Event::Closed)
            {
                window.close();
                return true;
            }
        }
    }
    return false;
}