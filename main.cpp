#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <string>

const bool DEBUG = true;

std::string ResourcePath = "C:/Users/Evan/Desktop/Files/Driving Game/";

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
	playerTexture.loadFromFile(ResourcePath + "Car/Car blue.png");
	player.setTexture(&playerTexture);
	player.setPosition(sf::Vector2f(295, 320));

	// Game Objects (obstacles & collectibles)

	// Background (currently only static)
	sf::RectangleShape bg(sf::Vector2f(640, 480));
	sf::Texture bgTexture;
	bgTexture.loadFromFile(ResourcePath + "BG/tempBG.png");
	bg.setTexture(&bgTexture);
	const int targetX[4] = { 204, 295, 388, 480 };	// Lane x-pos for car

	// Game Variables
	sf::Clock moveTimeout;		// Slows the rate of switching lane
	sf::Clock clock;			// clock used to track game runtime
	int numObstacles = 0;
	// double speed;	// will be used to change rate that objects and bg move
	int currentLane = 2;
	bool movingToLane = false;
	bool direction = false;		// false = left, true = right (given that movingToLane = true)


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

		// Window Redraw ----------
		window.clear();
		window.draw(bg);
		window.draw(player);
		window.display();

	}

	return 0;
}