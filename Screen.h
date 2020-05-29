#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"
class Screen
{
protected:
	sf::Font font;
	std::vector<sf::Text> line;
public:
	Screen() = default;
	virtual void draw(sf::RenderWindow& window) {};
	virtual void hoverSelected(int selection) {};
};



class Menu : public virtual Screen
{
protected:
	int selectedItemIndex;
public:
	Menu() :Screen() {};
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void hoverSelected(int selection);

	int getSelectedItemIndex() { return selectedItemIndex; }
};


class Control : public virtual Screen
{
	bool selectedBack;
public:
	Control() :Screen() {};
	Control(float width, float height);
	~Control();

	void draw(sf::RenderWindow& window);
	void hoverSelected(int selection);
	bool getSelectedBack() { return selectedBack; }
};

