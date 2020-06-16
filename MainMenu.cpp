#include "MainMenu.h"
#include "ControlMenu.h"
#include "FileNotFound.h"
#include "Constants.h"
#include "Instructions.h"

namespace cs = constants;

MainMenu::MainMenu() : Screen(), menuWindow(sf::VideoMode(cs::WINDOW_WIDTH, cs::WINDOW_HEIGHT), cs::MAIN_MENU_TITLE)
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
    temp.setStyle(sf::Text::Bold);
    temp.setOutlineColor(sf::Color::White);

    for (auto i = 0; i < cs::MENU_STRINGS.size(); i++)
    {
        if (i == 0)
        {
            temp.setCharacterSize(cs::MENU_TITLE_SIZE);
        }
        else
        {
            temp.setCharacterSize(cs::MENU_OPTIONS_SIZE);
        }
        temp.setOutlineThickness(cs::MENU_OUTLINE_THICKNESS[i]);

        temp.setFillColor(cs::MENU_FILL_COLOR[i]);
        temp.setString(cs::MENU_STRINGS[i]);
        temp.setPosition(cs::MENU_POSITIONS[i]);
        menuText.push_back(temp);
    }
    selectedItemIndex = 1;
}

bool MainMenu::startMenu()
{
    std::string path = cs::RESOURCE_PATH + cs::CAR_START_SFX;
    while (!music.openFromFile(path))
    {
        try { throw FileNotFound("Car Start SFX"); }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            path = e.resolve();
            if (path == "")
                break;
        }
    }
    music.setVolume(15);

    path = cs::RESOURCE_PATH + cs::BUTTON_SELECT_SFX;
    while (!buffer.loadFromFile(path))
    {
        try { throw FileNotFound("Button Select SFX"); }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            path = e.resolve();
            if (path == "")
                break;
        }
    }
    button.setBuffer(buffer);
    music.play();

    // Control Menu
    ControlMenu controls{};
    // Instruction Menu
    Instructions instructions{};

    bool showGame = false, showControls = false, showInstructions = false;

    while (menuWindow.isOpen())
    {
        while (menuWindow.pollEvent(menuScreen))
        {
            // mouse functionality
            double mouseX = sf::Mouse::getPosition(menuWindow).x;
            double mouseY = sf::Mouse::getPosition(menuWindow).y;

            // for the main menu
            if (!showControls && !showInstructions)
            {

                if (menuScreen.type == sf::Event::TextEntered && menuScreen.text.unicode < 128)
                {
                    int index = 0;
                    if (menuScreen.key.code == sf::Keyboard::BackSpace && menuScreen.type == sf::Event::KeyReleased &&
                        index > 0)
                        index--;

                    char buffer[5] = { 0, 0, 0, 0, 0 };
                    buffer[index] = static_cast<char>(menuScreen.text.unicode);

                    std::cout << buffer;
                }

                // keep track of which menu option is hovered using arrow keys
                if (menuScreen.key.code == sf::Keyboard::Up && menuScreen.type == sf::Event::KeyReleased)
                {
                    button.play();
                    move(-1);
                }
                if (menuScreen.key.code == sf::Keyboard::Down && menuScreen.type == sf::Event::KeyReleased)
                {
                    button.play();
                    move(1);
                }
                // which menu option is selected using enter key
                if (menuScreen.key.code == sf::Keyboard::Return && menuScreen.type == sf::Event::KeyReleased)
                {
                    if (getSelectedItemIndex() == 1) // "entered" play button
                        showGame = true;
                    else if (getSelectedItemIndex() == 2) //"entered" controls button
                        showControls = true;
                    else if (getSelectedItemIndex() == 3) //"entered" instructions button
                        showInstructions = true;
                    else if (getSelectedItemIndex() == 4) //"entered" exit button
                        menuWindow.close();
                }
                // mouse hovering the play button
                if ((mouseX > menuWindow.getSize().x * (.42) && mouseX < menuWindow.getSize().x * (.55)) &&
                    ((mouseY > menuWindow.getSize().y / 3.8) && (mouseY < menuWindow.getSize().y / 2.7)))
                {
                    if (getSelectedItemIndex() != 1)    // prevents music spam
                        button.play();

                    hoverSelected(1);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)  // clicks the play button
                        showGame = true;

                }
                // hovering the controls button
                else if ((mouseX > menuWindow.getSize().x * (.38) && mouseX < menuWindow.getSize().x * (.62)) &&
                    ((mouseY > menuWindow.getSize().y / 2.6) && (mouseY < menuWindow.getSize().y / 2.05)))
                {
                    if (getSelectedItemIndex() != 2)    // prevents music spam
                        button.play();

                    hoverSelected(2);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)  // clicks the control button
                    {
                        showControls = true;
                    }


                }

                // hovering the instructions button
                else if ((mouseX > menuWindow.getSize().x * (.43) && mouseX < menuWindow.getSize().x * (.60)) &&
                         ((mouseY > menuWindow.getSize().y / 2.0) && (mouseY < menuWindow.getSize().y / 1.63)))
                {
                    if (getSelectedItemIndex() != 3)    // prevents music spam
                    {
                        button.play();
                    }

                    hoverSelected(3);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)  // clicks the instructions button
                    {
                        showInstructions = true;
                    }
                }

                // hovering the exit button
                else if ((mouseX > menuWindow.getSize().x * (.43) && mouseX < menuWindow.getSize().x * (.55)) &&
                        ((mouseY > menuWindow.getSize().y / 1.9) && (mouseY < menuWindow.getSize().y / 1.2)))
                {
                    if (getSelectedItemIndex() != 4)    // prevents music spam
                    {
                        button.play();
                    }

                    hoverSelected(4);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)  // clicks the exit button
                    {
                        menuWindow.close();
                        return false;
                    }
                }
            }

            // Begin the game!
            if (showGame)
            {
                return true;
            }
            if (showControls)   // for the control menu
            {
                if ((mouseX < menuWindow.getSize().x / 6.2) && (mouseY > menuWindow.getSize().y * (.85))) {
                    if (!controls.getSelectedBack())
                        button.play();

                    controls.hoverSelected(1);

                    if (menuScreen.type == sf::Event::MouseButtonReleased)
                        showControls = false;

                } else {
                    controls.hoverSelected(0);
                }

                if (menuScreen.key.code == sf::Keyboard::Left && menuScreen.type == sf::Event::KeyReleased) {
                    showControls = false;
                }

                menuWindow.clear();
                controls.draw(menuWindow);
                menuWindow.display();
            }

            if (showInstructions)   // for the instruction menu
            {
                if ((mouseX < menuWindow.getSize().x / 6.2) && (mouseY > menuWindow.getSize().y * (.85)))
                {
                    if (!instructions.getSelectedBack())
                        button.play();

                    instructions.hoverSelected(1);

                    if (menuScreen.type == sf::Event::MouseButtonReleased)
                        showInstructions = false;

                }
                else
                {
                    instructions.hoverSelected(0);
                }

                if (menuScreen.key.code == sf::Keyboard::Left && menuScreen.type == sf::Event::KeyReleased)
                {
                    showInstructions = false;
                }

                menuWindow.clear();
                instructions.draw(menuWindow);
                menuWindow.display();
            }

            if (!showControls && !showInstructions)
            {
                menuWindow.clear();
                draw();
                menuWindow.display();
            }

            // if window is closed
            if (menuScreen.type == sf::Event::Closed)
            {
                menuWindow.close();
                return false;
            }
        }
    }
    return false;
}


void MainMenu::draw()
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

    texture.setSmooth(false);
    sf::Sprite background(texture);
    background.setScale(cs::MENU_BG_SCALE_X, cs::MENU_BG_SCALE_Y);
    menuWindow.draw(background);

    for (const auto& i : menuText)
    {
        menuWindow.draw(i);
    }
}


void MainMenu::move(int direction)
{
    menuText[selectedItemIndex].setFillColor(cs::HOVER_OFF_COLOR.first);
    menuText[selectedItemIndex].setOutlineThickness(cs::HOVER_OFF_COLOR.second);

    if (direction < 0)
    {
        if (selectedItemIndex != 1)
            selectedItemIndex--;
    }
    else
    {
        if (selectedItemIndex != 4)
            selectedItemIndex++;
    }

    menuText[selectedItemIndex].setFillColor(cs::HOVER_ON_COLOR.first);
    menuText[selectedItemIndex].setOutlineThickness(cs::HOVER_ON_COLOR.second);
}

void MainMenu::hoverSelected(int selection)
{
    menuText[selectedItemIndex].setFillColor(cs::HOVER_OFF_COLOR.first);
    menuText[selectedItemIndex].setOutlineThickness(cs::HOVER_OFF_COLOR.second);

    menuText[selection].setFillColor(cs::HOVER_ON_COLOR.first);
    menuText[selection].setOutlineThickness(cs::HOVER_ON_COLOR.second);
    selectedItemIndex = selection;
}


MainMenu::~MainMenu()
{
    menuWindow.close();
}
