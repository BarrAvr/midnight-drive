#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <string>
#include <array>
#include <ctime>

const bool DEBUG = true;
using namespace std;

//std::string ResourcePath = "C:/Users/Evan/Desktop/Files/Driving Game/";

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
	playerTexture.loadFromFile("Car blue.png");
	player.setTexture(&playerTexture);
	player.setPosition(sf::Vector2f(295, 320));

	// Game Objects (obstacles & collectibles)
	array<string, 15> obstacleArray = {"Trash can.png", "Trash can fallen.png", "Traffic cone.png", "Street baracade.png", "Street baracade 2.png",
	     "Construction sign.png", "Oil can.png", "Left sign broken.png", "Right sign broken.png", "Speed sign broken.png", "Stop sign broken.png", 
	    "Stripped sign 1.png", "Pot hole.png", "Cracks.png", "Man hole.png"};
	sf::RectangleShape obstacle(sf::Vector2f(100.0f, 100.0f));
	sf::Texture obstacleTexture;
	srand(time(NULL));

	// Background (currently only static)
	sf::RectangleShape bg1(sf::Vector2f(640, 480));
	sf::Texture bgTexture1;
	bgTexture1.loadFromFile("background.png");
	bg1.setTexture(&bgTexture1);
	
	sf::RectangleShape bg2(sf::Vector2f(640, 480));
	sf::Texture bgTexture2;
	bgTexture2.loadFromFile("background.png");
	bg2.setTexture(&bgTexture2);
	bg2.setPosition(sf::Vector2f(0, -480));

	// Game Variables
	sf::Clock moveTimeout;		// Slows the rate of switching lane
	sf::Clock clock;			// clock used to track game runtime
	int numObstacles = 0;
	// double speed;	// will be used to change rate that objects and bg move
	int currentLane = 2;
	bool movingToLane = false;
	bool direction = false;		// false = left, true = right (given that movingToLane = true)
	const int targetX[4] = { 204, 295, 388, 480 };	// Lane x-pos for car
    
    

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (currentLane < 4) && (moveTimeout.getElapsedTime().asMilliseconds() > 200))
		{
			currentLane++;
			movingToLane = true;
			direction = true;
			std::cout << "Moving to lane: " << currentLane << std::endl;
			moveTimeout.restart();
		}
		// Move Left
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (currentLane > 1) && (moveTimeout.getElapsedTime().asMilliseconds() > 200))
		{
			currentLane--;
			movingToLane = true;
			direction = false;
			std::cout << "Moving to lane: " << currentLane << std::endl;
			moveTimeout.restart();
		}

		if(movingToLane)
		{
			// right: +10 x-pos		left: -10 x-pos
			player.move(sf::Vector2f(direction ? 10 : -10, 0));

			int targetPos = targetX[currentLane-1];	// lane x-pos
			int playerPos = player.getPosition().x;

			if(DEBUG)	std::cout << "pos: " << playerPos << std::endl;

			// stop moving if car is in the correct lane
			if (playerPos >= (targetPos -5) && playerPos <= (targetPos +5))
			{
				movingToLane = false;
				std::cout << "movingLanes = false" << std::endl << std::endl;
			}

		}
		
        if (clock.getElapsedTime().asSeconds() > 3)
        {	
            // Random number to choose which obstacle to display
            int oNumber = rand() % 15;
            // Random number to choose x coordinate
            int xNumber = 204 + rand() % ((480 + 1) - 204);
            // Random number to choose y coordinate
            int yNumber = 10 + rand() % ((40 + 1) - 10);
                
	        obstacleTexture.loadFromFile(obstacleArray[oNumber]);
	        obstacle.setTexture(&obstacleTexture);
	        obstacle.setPosition(sf::Vector2f(xNumber, yNumber));
            clock.restart();
            

        }
        
        // Scrolling obstacles
        if(obstacle.getPosition().y < window.getSize().y)
            obstacle.move(sf::Vector2f(0, 10));

        /**
        For scrolling background
        if(bg1.getPosition().y < window.getSize().y || bg2.getPosition().y < window.getSize().y)
        {
            bg1.move(sf::Vector2f(0, 10));
            bg2.move(sf::Vector2f(0, 10));
            if(bg1.getPosition().y == 490)
                bg1.setPosition(sf::Vector2f(0, -480));
            if(bg2.getPosition().y == 490)
                bg2.setPosition(sf::Vector2f(0, -480));
        }
        **/	

		// Window Redraw ----------
		window.clear();
		window.draw(bg1);
		window.draw(bg2);
		window.draw(player);
		window.draw(obstacle);
		window.display();

	}

	return 0;
}