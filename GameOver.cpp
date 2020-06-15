#include "GameOver.h"
#include "Constants.h"
#include "NameInput.h"

namespace cs = constants;

GameOver::GameOver(const Score& newScore) : window_(sf::VideoMode(cs::WindowWidth_, cs::WindowHeight_), cs::GameOverTitle), newScore_(newScore)
{
    scoreboard.readScoresFromFile(cs::scoreboardPath);
    //TODO: file exception
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
    temp.setString("Leader Boards:");
    temp.setPosition(sf::Vector2f(cs::WindowWidth_ * .1, 180));
    line.push_back(temp);


    temp.setStyle(sf::Text::Regular);
    temp.setStyle(sf::Text::Bold);
    temp.setString("Exit Game");
    temp.setPosition(sf::Vector2f(cs::WindowWidth_ * .37, cs::WindowHeight_ * .8));
    line.push_back(temp);

    selectedExit = false;
}


//cant add in the default constructor because we read the score laterrr
void GameOver::addScoresToScreen()
{
    //FOR THE SCOREBOARD
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
    for (auto i = 0; i < 5; i++) //print out first column of scores;
    {
        std::string scoreTemp;
        if (scoreboard.getScores()[i].second == "-----")
            scoreTemp = "---";
        else
        {
            scoreTemp = std::to_string(scoreboard.getScores()[i].first.getScore());
        }
        std::string scoreLine = std::to_string(i + 1) + ". " + scoreTemp + " : " + scoreboard.getScores()[i].second;
        temp.setString(scoreLine);
        temp.setPosition(sf::Vector2f(150, 270 + (i * 60)));
        scoresLine.push_back(temp);
    }

    for (auto i = 5; i < 10; i++) //print out second column of scores
    {
        std::string scoreTemp;
        if (scoreboard.getScores()[i].second == "-----")
            scoreTemp = "---";
        else
            scoreTemp = std::to_string(scoreboard.getScores()[i].first.getScore());

        std::string scoreLine = std::to_string(i + 1) + ". " + scoreTemp + " : " + scoreboard.getScores()[i].second;
        temp.setString(scoreLine);
        if (i < 9)
            temp.setPosition(sf::Vector2f(600, 270 + ((i - 5) * 60)));
        else
            temp.setPosition(sf::Vector2f(580, 270 + ((i - 5) * 60)));

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

    } else
    {
        selectedExit = false;
        line[2].setOutlineThickness(3);
        line[2].setFillColor(sf::Color::Black);
    }
}

void GameOver::draw(sf::RenderWindow& window)
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

    window.draw(line[0]);
    window.draw(line[1]);
    window.draw(line[2]);

    for (auto i = 0; i < 10; i++)
        window.draw(scoresLine[i]);
}

void GameOver::startGameOver()
{
    // name input
    NameInput nameInput{};

    bool enterName = true;

    while (window_.isOpen())
    {

        while (window_.pollEvent(menuScreen))
        {
            double mouseX = sf::Mouse::getPosition(window_).x;
            double mouseY = sf::Mouse::getPosition(window_).y;

            if (menuScreen.type == sf::Event::Closed)
            {
                window_.close();
            }

            //here is after the game ends it goes into the name input screen, and then into the gameover
            //NAMEINPUT SCREEN
            if (enterName)
            {
                if (menuScreen.type == sf::Event::Closed)
                {
                    window_.close();
                }

                if (menuScreen.type == sf::Event::TextEntered)
                {
                    nameInput.typedOn(menuScreen);
                }

                //for mouse functionality
                if ((mouseX > window_.getSize().x * .38 && mouseX < window_.getSize().x * .63) &&
                    (mouseY > window_.getSize().y * .57 && mouseY < window_.getSize().y * .66))
                {
                    if (!nameInput.getContinueSelected())
                    {
                        button.play();
                    }
                    nameInput.hoverSelected(1);

                    if (menuScreen.type == sf::Event::MouseButtonReleased)
                    {
                        //EXAMPLE ADDING A SCORE
                        scoreboard.addScore(newScore_, nameInput.getName());
                        addScoresToScreen();
                        enterName = false;
                    }
                } else
                {
                    nameInput.hoverSelected(0);
                }

                //for enter key functionality
                if (menuScreen.key.code == sf::Keyboard::Return && menuScreen.type == sf::Event::KeyReleased)
                {
                    //EXAMPLE ADDING A SCORE
                    scoreboard.addScore(newScore_, nameInput.getName());
                    addScoresToScreen();
                    enterName = false;
                }

                window_.clear();
                nameInput.draw(window_);
                window_.display();
            }

            if (!enterName)
            {
                //GAMEOVERSCREEN ONCE ENTERED PRESSED FOR NAME INPUT
                if ((mouseX > window_.getSize().x * .35 && mouseX < window_.getSize().x * .9) &&
                    (mouseY > window_.getSize().y * .8 && mouseY < window_.getSize().y * .91))
                {
                    if (!getSelectedExit())
                    {
                        button.play();
                    }

                    hoverSelected(1);
                    if (menuScreen.type == sf::Event::MouseButtonReleased)
                    {
                        window_.close();
                    }
                } else
                    hoverSelected(0);

                window_.clear();
                draw(window_);
                window_.display();
            }
        }
    }
}

GameOver::~GameOver()
{
    scoreboard.writeScoresToFile(cs::scoreboardPath);
    window_.close();
}
