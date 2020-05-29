#include "Screen.h"



Menu::Menu(float width, float height)
{
	//NEED TO IMPLEMENT FILE CHECK HERE!
	if (!font.loadFromFile("double_pixel-7.ttf"))
	{
		//bad stuff happens
	}

	sf::Text temp;
	temp.setFont(font);
	temp.setOutlineThickness(3);
	temp.setOutlineColor(sf::Color::White);
	temp.setFillColor(sf::Color(226, 183, 10));
	temp.setStyle(sf::Text::Bold);
	temp.setCharacterSize(140);
	temp.setString("MIDNIGHT DRIVE");
	temp.setPosition(sf::Vector2f(width / 9.4, 50));
	line.push_back(temp);

	temp.setOutlineThickness(4);
	temp.setOutlineColor(sf::Color::White);
	temp.setCharacterSize(80);
	temp.setFillColor(sf::Color::Blue);
	temp.setString("Play");
	temp.setPosition(sf::Vector2f(width / 2.28, height / 3.8));
	line.push_back(temp);

	temp.setOutlineThickness(2.5);
	temp.setFillColor(sf::Color::Black);
	temp.setString("Controls");
	temp.setPosition(sf::Vector2f(width / 2.54, height / 2.6));
	line.push_back(temp);

	temp.setString("Exit");
	temp.setPosition(sf::Vector2f(width / 2.26, height / 2));
	line.push_back(temp);

	selectedItemIndex = 1;
}

//do i even need a destructor?
Menu::~Menu()
{
}


void Menu::draw(sf::RenderWindow& window)
{

	sf::Texture texture;
	//NEED TO IMPLEMENT FILE CHECK HERE!
	if (!texture.loadFromFile("pixel_background.png"));
	{
		
	}

	texture.setSmooth(false);
	sf::Sprite background(texture);
	background.setScale(2.5, 2);
	window.draw(background);

	window.draw(line[0]);
	window.draw(line[1]);
	window.draw(line[2]);
	window.draw(line[3]);
	
}

void Menu::MoveUp()
{
	if (selectedItemIndex > 1)
	{
		line[selectedItemIndex].setFillColor(sf::Color::Black);
		line[selectedItemIndex].setOutlineThickness(2.5);

		selectedItemIndex--;
		line[selectedItemIndex].setFillColor(sf::Color::Blue);
		line[selectedItemIndex].setOutlineThickness(4);

	}
}
void Menu::MoveDown()
{
	if (selectedItemIndex < 3)
	{
		line[selectedItemIndex].setFillColor(sf::Color::Black);
		line[selectedItemIndex].setOutlineThickness(2.5);

		selectedItemIndex++;
		line[selectedItemIndex].setFillColor(sf::Color::Blue);
		line[selectedItemIndex].setOutlineThickness(4);

	}
}

void Menu::hoverSelected(int selection)
{
	line[selectedItemIndex].setFillColor(sf::Color::Black);
	line[selectedItemIndex].setOutlineThickness(2.5);

	line[selection].setFillColor(sf::Color::Blue);
	line[selection].setOutlineThickness(4);
	selectedItemIndex = selection;
}

















Control::Control(float width, float height)
{

	//NEED TO IMPLEMENT FILE CHECK HERE!
	if (!font.loadFromFile("double_pixel-7.ttf"))
	{
		//bad stuff happens
	}

	sf::Text temp;
	
	temp.setFont(font);
	temp.setOutlineThickness(3);
	temp.setOutlineColor(sf::Color::White);
	temp.setFillColor(sf::Color(226, 183, 10));
	temp.setStyle(sf::Text::Bold);
	temp.setCharacterSize(100);
	temp.setString("Controls");
	temp.setPosition(sf::Vector2f(width / 2.78, 80));
	line.push_back(temp);


	temp.setFont(font);
	temp.setOutlineThickness(3);
	temp.setOutlineColor(sf::Color::White);
	temp.setCharacterSize(60);
	temp.setFillColor(sf::Color::Black);
	temp.setString("<- -> arrow keys to");
	temp.setPosition(sf::Vector2f(width / 3, height / 3.4));
	line.push_back(temp);

	temp.setString("switch lanes");
	temp.setPosition(sf::Vector2f(width / 3, height / 2.85));

	line.push_back(temp);


	temp.setString("P to pause");
	temp.setPosition(sf::Vector2f(width / 3, height / 2));

	line.push_back(temp);

	temp.setCharacterSize(80);
	temp.setString("Back");
	temp.setPosition(sf::Vector2f(40, height - 120));

	line.push_back(temp);

	selectedBack = false;

}

//do i even need a destructor?
Control::~Control()
{
}

void Control::draw(sf::RenderWindow& window)
{
	sf::Texture texture;

	//NEED TO IMPLEMENT FILE CHECK HERE!
	if (!texture.loadFromFile("pixel_background.png"))
	{
		//bad stuff happens
	}

	sf::Sprite background(texture);
	background.setScale(2.5, 2);
	window.draw(background);

	window.draw(line[0]);
	window.draw(line[1]);
	window.draw(line[2]);
	window.draw(line[3]);
	window.draw(line[4]);

}

void Control::hoverSelected(int selection)
{
	if (selection == 1)
	{
		selectedBack = true;
		line[4].setOutlineThickness(4);
		line[4].setFillColor(sf::Color::Blue);
	}
	else {
		selectedBack = false;
		line[4].setOutlineThickness(3);
		line[4].setFillColor(sf::Color::Black);
	}
		

}