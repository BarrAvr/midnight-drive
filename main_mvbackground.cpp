#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <string>
#include <array>
#include <ctime>

const bool DEBUG = true;
using namespace std;

std::string ResourcePath = "/home/dlieber/Downloads/Car_game_v4/";

static int bgChangeCounter = 0;
static std::vector<sf::RectangleShape> objects;
vector<string> backgrounds_{"b0.png", "b1.png", "b2.png",
                            "b3.png", "b4.png",
                            "b5.png", "b6.png",
                            "b7.png", "b8.png", "b9.png"};
static int currBg;

int main()
{
    unsigned frameRate = 30;
    sf::RenderWindow window(sf::VideoMode(640, 480), "Driving Game v0.001a");
    window.setFramerateLimit(frameRate);

// Title Screen & High Score List -------------------------------
    // ......

// Game Graphics Setup ------------------------------------------

    // change window size if game & title screens have different dimentions
    // window.setSize(sf::Vector2u(640.0f, 480.0f));

    // Player Car
    sf::RectangleShape player(sf::Vector2f(128.0f, 128.0f));
    sf::Texture playerTexture;
    playerTexture.loadFromFile(ResourcePath + "Car blue.png");
    player.setTexture(&playerTexture);
    player.setPosition(sf::Vector2f(250, 320));

    // Game Objects (obstacles & collectibles)
    array<string, 15> ar = {"Trash can.png", "Trash can fallen.png", "Traffic cone.png",
                            "Street baracade.png", "Street baracade 2.png",
                            "Construction sign.png", "Oil can.png",
                            "Left sign broken.png", "Right sign broken.png", "Speed sign broken.png",
                            "Stop sign broken.png",
                            "Stripped sign 1.png", "Pot hole.png",
                            "Cracks.png", "Man hole.png"};
    sf::RectangleShape obstacle(sf::Vector2f(100.0f, 100.0f));
    sf::Texture obstacleTexture;
    srand(time(NULL));

    // Background (currently only static)
    sf::RectangleShape bg(sf::Vector2f(640, 480));
    sf::Texture bgTexture;
    //bgTexture.loadFromFile(ResourcePath + "background.png");
    //bg.setTexture(&bgTexture);
    const int targetX[4] = {120, 250, 370, 480};    // Lane x-pos for car

    // Game Variables
    sf::Clock moveTimeout;        // Slows the rate of switching lane
    sf::Clock clock;            // clock used to track game runtime
    // int numObstacles = 0;
    // double speed;	// will be used to change rate that objects and bg move
    int currentLane = 2;
    bool movingToLane = false;
    bool direction = false;        // false = left, true = right (given that movingToLane = true)


// Main Game Loop -----------------------------------------------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move Right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (currentLane < 4) &&
            (moveTimeout.getElapsedTime().asMilliseconds() > 200))
        {
            currentLane++;
            movingToLane = true;
            direction = true;
            std::cout << "Moving to lane: " << currentLane << std::endl;
            moveTimeout.restart();
        }
            // Move Left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (currentLane > 1) &&
                 (moveTimeout.getElapsedTime().asMilliseconds() > 200))
        {
            currentLane--;
            movingToLane = true;
            direction = false;
            std::cout << "Moving to lane: " << currentLane << std::endl;
            moveTimeout.restart();
        }

        if (movingToLane)
        {
            // right: +10 x-pos		left: -10 x-pos
            player.move(sf::Vector2f(direction ? 10 : -10, 0));

            int targetPos = targetX[currentLane - 1];    // lane x-pos
            int playerPos = player.getPosition().x;

            if (DEBUG) std::cout << "pos: " << playerPos << std::endl;

            // stop moving if car is in the correct lane
            if (playerPos >= (targetPos - 5) && playerPos <= (targetPos + 5))
            {
                movingToLane = false;
                std::cout << "movingLanes = false" << std::endl << std::endl;
            }

        }

        if (clock.getElapsedTime().asSeconds() > 5)
        {
            // Random number to choose which obstacle to display
            int oNumber = rand() % 15;
            // Random number to choose x coordinate
            int xNumber = 204 + rand() % ((480 + 1) - 204);
            // Random number to choose y coordinate
            int yNumber = 10 + rand() % ((40 + 1) - 10);

            obstacleTexture.loadFromFile(ResourcePath + ar[oNumber]);
            obstacle.setTexture(&obstacleTexture);
            obstacle.setPosition(sf::Vector2f(xNumber, yNumber));
            objects.push_back(obstacle);
            clock.restart();
        }

        // Window Redraw ----------
        window.clear();
        bgChangeCounter++;
        if (bgChangeCounter == 6)
        {
            currBg++;
            bgChangeCounter = 0;
        }

        if (currBg > backgrounds_.size() - 1)
        {
            currBg = 0;
        }

        bgTexture.loadFromFile(ResourcePath + backgrounds_.at(currBg));
        bg.setTexture(&bgTexture);

        window.draw(bg);
        window.draw(player);

        for (auto obj = objects.begin(); obj != objects.end(); ++obj)
        {
            auto oldPos = obj->getPosition();
            obj->setPosition(oldPos.x, oldPos.y + 3);
            if (obj->getPosition().y <= 630) {
                window.draw(*obj);
            } else {
                objects.erase(obj);
            }
        }

        window.display();
    }

    return 0;
}