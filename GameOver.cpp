#include "GameOver.h"
#include "NameInput.h"
#include "FileNotFound.h"
#include "Constants.h"

namespace cs = constants;

GameOver::GameOver(const Score& newScore) : gameoverWindow(sf::VideoMode(cs::WINDOW_WIDTH, cs::WINDOW_HEIGHT), cs::GAME_OVER_TITLE), newScore(newScore)
{
    scoreboard.readScoresFromFile(cs::SCOREBOARD_PATH);

    std::string fontPath = cs::RESOURCE_PATH + cs::FONT;
    while (!font.loadFromFile(fontPath))
    {
        try
        {
            throw FileNotFound("Game Font");
        }
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
    temp.setOutlineThickness(3);
    temp.setOutlineColor(sf::Color::White);
    temp.setFillColor(sf::Color::Red);
    temp.setStyle(sf::Text::Bold);
    temp.setCharacterSize(120);
    temp.setString("GAME OVER");
    temp.setPosition(sf::Vector2f(cs::WINDOW_WIDTH * .28, 50));
    line.push_back(temp);

    temp.setOutlineThickness(3);
    temp.setOutlineColor(sf::Color::White);
    temp.setFillColor(sf::Color::Black);
    temp.setStyle(sf::Text::Bold);
    temp.setStyle(sf::Text::Underlined);
    temp.setCharacterSize(80);
    temp.setString("Leader Boards:");
    temp.setPosition(sf::Vector2f(cs::WINDOW_WIDTH * .1, 180));
    line.push_back(temp);


    temp.setStyle(sf::Text::Regular);
    temp.setStyle(sf::Text::Bold);
    temp.setString("Exit Game");
    temp.setPosition(sf::Vector2f(cs::WINDOW_WIDTH * .37, cs::WINDOW_HEIGHT * .8));
    line.push_back(temp);

    selectedExit = false;
}

void GameOver::addScoresToScreen()
{
    sf::Text temp;
    temp.setFont(font);
    temp.setOutlineThickness(3);
    temp.setOutlineColor(sf::Color::White);
    temp.setFillColor(sf::Color::Black);
    temp.setStyle(sf::Text::Bold);
    temp.setCharacterSize(120);
    temp.setString("GAME OVER");
    temp.setPosition(sf::Vector2f(280, 50));
    line.push_back(temp);
    temp.setCharacterSize(60);

    // Print out first column of scores
    for (auto i = 0; i < 5; i++)
    {
        std::string scoreTemp;
        if (scoreboard.getScores()[i].second == "-----")
        {
            scoreTemp = "---";
        }
        else
        {
            scoreTemp = std::to_string(scoreboard.getScores()[i].first.getScore());
        }
        std::string scoreLine = std::to_string(i + 1) + ". " + scoreTemp + " : " + scoreboard.getScores()[i].second;
        temp.setString(scoreLine);
        temp.setPosition(sf::Vector2f(150, 270 + (i * 60)));
        scoresLine.push_back(temp);
    }

    // Print out second column of scores
    for (auto i = 5; i < 10; i++)
    {
        std::string scoreTemp;
        if (scoreboard.getScores()[i].second == "-----")
        {
            scoreTemp = "---";
        }
        else
        {
            scoreTemp = std::to_string(scoreboard.getScores()[i].first.getScore());
        }

        std::string scoreLine = std::to_string(i + 1) + ". " + scoreTemp + " : " + scoreboard.getScores()[i].second;
        temp.setString(scoreLine);
        if (i < 9)
        {
            temp.setPosition(sf::Vector2f(600, 270 + ((i - 5) * 60)));
        }
        else
        {
            temp.setPosition(sf::Vector2f(580, 270 + ((i - 5) * 60)));
        }

        scoresLine.push_back(temp);
    }
}

void GameOver::hoverSelected(int selection)
{
    if (selection > 0)
    {
        selectedExit = true;
        line[2].setOutlineThickness(4);
        line[2].setFillColor(sf::Color::Blue);

    }
    else
    {
        selectedExit = false;
        line[2].setOutlineThickness(3);
        line[2].setFillColor(sf::Color::Black);
    }
}

void GameOver::draw(sf::RenderWindow& window)
{
    sf::Texture texture;
    std::string texturePath = cs::RESOURCE_PATH + cs::MENU_BACKGROUND2;
    while (!texture.loadFromFile(texturePath))
    {
        try
        {
            throw FileNotFound("Pixel Background 2 Texture");
        }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            texturePath = e.resolve();
            if (texturePath == "")
                break;
        }
    }

    sf::Sprite background(texture);
    background.setScale(2, 2);
    window.draw(background);

    window.draw(line[0]);
    window.draw(line[1]);
    window.draw(line[2]);

    for (auto i = 0; i < 10; i++)
    {
        window.draw(scoresLine[i]);
    }
}

// Name Entry
void GameOver::startGameOver()
{
    NameInput nameInput{};
    bool enterName = true;

    while (gameoverWindow.isOpen())
    {
        while (gameoverWindow.pollEvent(menuScreen))
        {
            double mouseX = sf::Mouse::getPosition(gameoverWindow).x;
            double mouseY = sf::Mouse::getPosition(gameoverWindow).y;

            if (menuScreen.type == sf::Event::Closed)
            {
                gameoverWindow.close();
            }

            // Input Screen
            if (enterName)
            {
                if (menuScreen.type == sf::Event::Closed)
                {
                    gameoverWindow.close();
                }
                if (menuScreen.type == sf::Event::TextEntered)
                {
                    nameInput.typedOn(menuScreen);
                }

                // for mouse functionality
                if ((mouseX > gameoverWindow.getSize().x * .38 && mouseX < gameoverWindow.getSize().x * .63) &&
                    (mouseY > gameoverWindow.getSize().y * .57 && mouseY < gameoverWindow.getSize().y * .66))
                {
                    if (!nameInput.getContinueSelected())
                    {
                        button.play();
                    }
                    nameInput.hoverSelected(1);

                    if (menuScreen.type == sf::Event::MouseButtonReleased)
                    {
                        scoreboard.addScore(newScore, nameInput.getName());
                        addScoresToScreen();
                        enterName = false;
                    }
                }
                else
                {
                    nameInput.hoverSelected(0);
                }

                // for enter key functionality
                if (menuScreen.key.code == sf::Keyboard::Return && menuScreen.type == sf::Event::KeyReleased)
                {
                    scoreboard.addScore(newScore, nameInput.getName());
                    addScoresToScreen();
                    enterName = false;
                }

                gameoverWindow.clear();
                nameInput.draw(gameoverWindow);
                gameoverWindow.display();
            }

            // User has submitted name
            if (!enterName)
            {
                if ((mouseX > gameoverWindow.getSize().x * .35 && mouseX < gameoverWindow.getSize().x * .9) &&
                    (mouseY > gameoverWindow.getSize().y * .8 && mouseY < gameoverWindow.getSize().y * .91))
                {
                    if (!getSelectedExit())
                    {
                        button.play();
                    }

                    hoverSelected(1);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)
                    {
                        gameoverWindow.close();
                    }
                }
                else
                {
                    hoverSelected(0);
                }

                gameoverWindow.clear();
                draw(gameoverWindow);
                gameoverWindow.display();
            }
        }
    }
}

GameOver::~GameOver()
{
    scoreboard.writeScoresToFile(cs::SCOREBOARD_PATH);
    gameoverWindow.close();
}
