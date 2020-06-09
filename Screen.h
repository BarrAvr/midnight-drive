#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"
#include "Scoreboard.h"
#include "Textbox.h"

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


//NEW CHANGES HERE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NameInput : public virtual Screen
{
private:
	bool continueSelected;
	sf::Text textbox;
	std::ostringstream text;
public:
	using Score = std::pair<int, string>;

	NameInput() = default;
	NameInput(float width, float height);
	void draw(sf::RenderWindow& window);
	void hoverSelected(int selection);
	void inputLogic(int charTyped);
	void deleteLastChar();
	void typedOn(sf::Event input);
	Score addScoreToFile(ostream& file);
	std::string getName();
	bool getContinueSelected() { return continueSelected; }

};


class GameOver : public virtual Screen
{
private:
	bool selectedExit;
	std::vector<sf::Text> scoresLine;

public:
	GameOver() :Screen() {};
	GameOver(float width, float height);
	void draw(sf::RenderWindow& window);
	void hoverSelected(int selection);
	bool getSelectedExit() { return selectedExit; }
	void addScoresToScreen(Scoreboard& score);

};


////////////////////////////////////////////////////////////////////////////////////////////////////




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
