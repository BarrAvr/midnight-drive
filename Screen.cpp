#include "Screen.h"
#include <string>


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
	background.setScale(2, 2);
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
	background.setScale(2, 2);
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







//NEW CHANGES HERE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameOver::GameOver(float width, float height)
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
	temp.setFillColor(sf::Color::Red);
	temp.setStyle(sf::Text::Bold);
	temp.setCharacterSize(120);
	temp.setString("GAME OVER");
	temp.setPosition(sf::Vector2f(width *.28, 50));
	line.push_back(temp);

	temp.setOutlineThickness(3);
	temp.setOutlineColor(sf::Color::White);
	temp.setFillColor(sf::Color::Black);
	temp.setStyle(sf::Text::Bold);
	temp.setStyle(sf::Text::Underlined);
	temp.setCharacterSize(80);
	temp.setString("Leader Boards:");
	temp.setPosition(sf::Vector2f(width * .1, 180));
	line.push_back(temp);

	
	temp.setStyle(sf::Text::Regular);
	temp.setStyle(sf::Text::Bold);
	temp.setString("Exit Game");
	temp.setPosition(sf::Vector2f(width *.37, height *.8));
	line.push_back(temp);


	selectedExit = false;
}


//cant add in the default constructor because we read the score laterrr
void GameOver::addScoresToScreen(Scoreboard& score)
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
		string scoreTemp;
		if (!score.getScores()[i].second.compare("-----"))
			scoreTemp = "---";
		else
			scoreTemp = to_string(score.getScores()[i].first);

		string scoreLine = to_string(i + 1) + ". " + scoreTemp + " : " + score.getScores()[i].second;
		temp.setString(scoreLine);
		temp.setPosition(sf::Vector2f(150, 270 + (i * 60)));
		scoresLine.push_back(temp);
	}

	for (auto i = 5; i < 10; i++) //print out second column of scores
	{
		string scoreTemp;
		if (!score.getScores()[i].second.compare("-----"))
			scoreTemp = "---";
		else
			scoreTemp = to_string(score.getScores()[i].first);

		string scoreLine = to_string(i + 1) + ". " + scoreTemp + " : " + score.getScores()[i].second;
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

	}
	else {
		selectedExit = false;
		line[2].setOutlineThickness(3);
		line[2].setFillColor(sf::Color::Black);
	}
}

void GameOver::draw(sf::RenderWindow& window)
{
	sf::Texture texture;

	//NEED TO IMPLEMENT FILE CHECK HERE!
	if (!texture.loadFromFile("pixel_background2.png"))
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


















NameInput::NameInput(float width, float height)
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
	temp.setFillColor(sf::Color::Red);
	temp.setStyle(sf::Text::Bold);
	temp.setCharacterSize(120);
	temp.setString("GAME OVER");
	temp.setPosition(sf::Vector2f(width * .28, 50));
	line.push_back(temp);

	temp.setOutlineThickness(3);
	temp.setOutlineColor(sf::Color::White);
	temp.setFillColor(sf::Color::Black);
	temp.setStyle(sf::Text::Bold);
	temp.setStyle(sf::Text::Underlined);
	temp.setCharacterSize(80);
	temp.setString("Enter your name:");
	temp.setPosition(sf::Vector2f(width * .1, height * .36));
	line.push_back(temp);

	temp.setStyle(sf::Text::Regular);
	temp.setStyle(sf::Text::Bold);
	temp.setString("Continue");
	temp.setPosition(sf::Vector2f(width * .4, height * .55));
	line.push_back(temp);

	textbox.setFont(font);
	textbox.setCharacterSize(80);
	textbox.setFillColor(sf::Color::Black);
	textbox.setOutlineThickness(3);
	textbox.setOutlineColor(sf::Color::White);
	textbox.setPosition(sf::Vector2f(width * .6, height*.36));

	textbox.setString("_");

	continueSelected = false;
}

void NameInput::inputLogic(int charTyped)
{
	//8 is the delete key, 13 is the enter key
	if (charTyped != 8 && charTyped != 13 && text.str().length() < 7)
		text << static_cast<char>(charTyped);
	else if (charTyped == 8) //enter is pressed
	{
		if (text.str().length() > 0)
			deleteLastChar();
	}
	

	if (text.str().length() < 7)
		textbox.setString(text.str() + "_");
	else
		textbox.setString(text.str());
}

void NameInput::deleteLastChar()
{
	std::string t = text.str();
	std::string newt = "";
	for (int i = 0; i < t.length() - 1; i++)
	{
		newt += t[i];
	}

	text.str("");
	text << newt;

	textbox.setString(text.str());
}

void NameInput::typedOn(sf::Event input)
{
	int charTyped = input.text.unicode;
	
	if (charTyped < 128)
		inputLogic(charTyped);
	
	
}


void NameInput::draw(sf::RenderWindow& window)
{
	sf::Texture texture;

	//NEED TO IMPLEMENT FILE CHECK HERE!
	if (!texture.loadFromFile("pixel_background2.png"))
	{
		//bad stuff happens
	}

	
	sf::Sprite background(texture);
	background.setScale(2, 2);
	window.draw(background);

	window.draw(textbox);
	window.draw(line[0]);
	window.draw(line[1]);
	window.draw(line[2]);

}

std::string NameInput::getName()
{
	return text.str();
}

void NameInput:: hoverSelected(int selection)
{
	if (selection == 1)
	{
		continueSelected = true;
		line[2].setOutlineThickness(4);
		line[2].setFillColor(sf::Color::Blue);
	}
	else
	{
		continueSelected = false;
		line[2].setOutlineThickness(3);
		line[2].setFillColor(sf::Color::Black);
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////