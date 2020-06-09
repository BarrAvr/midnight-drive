#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "Scoreboard.h"
#include "Textbox.h"
#define windowx 1000
#define windowy 800

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowx ,windowy), "Driving Game");
	sf::Event menuScreen;
	
	sf::Music music;
	//need to implement file check stuff here
	music.openFromFile("background_music.wav");
	
	sf::Music carDriving;
	//need to implement file check stuff here
	carDriving.openFromFile("carstart.wav");

	sf::SoundBuffer buffer;
	//need to implement file check stuff here
	buffer.loadFromFile("button_select.wav");

	sf::Sound button;
	button.setBuffer(buffer);

	music.play();


	//temp scoreboard
	Scoreboard scores;

	//main menu
	Menu menu(window.getSize().x, window.getSize().y);
	//control menu
	Control controls(window.getSize().x, window.getSize().y);

	


	bool playMenu = false, controlMenu = false, gameoverMenu = false;


	//NEW CHANGES HERE
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//gameover menu
	GameOver gameover(window.getSize().x,window.getSize().y);

	NameInput nameInput(window.getSize().x, window.getSize().y);

	
	bool enterName = true;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	menu.draw(window);
	window.display();
	string temp;
while (window.isOpen())
{
	while (window.pollEvent(menuScreen))
	{
		//mouse functionality
		double mouseX = sf::Mouse::getPosition(window).x;
		double mouseY = sf::Mouse::getPosition(window).y;


		//for the main menu
		if (playMenu == false && controlMenu == false)
		{

			if (menuScreen.type == sf::Event::TextEntered && menuScreen.text.unicode < 128)
			{
				int index = 0;
				if (menuScreen.key.code == sf::Keyboard::BackSpace && menuScreen.type == sf::Event::KeyReleased && index > 0)
					index--;

				char buffer[5] = {0,0,0,0,0};
				buffer[index] = static_cast<char>(menuScreen.text.unicode);

				cout << buffer;


			}

			//keep track of which menu option is hovered using arrow keys
			if (menuScreen.key.code == sf::Keyboard::Up && menuScreen.type == sf::Event::KeyReleased)
			{
				button.play();
				menu.MoveUp();
			}
			if (menuScreen.key.code == sf::Keyboard::Down && menuScreen.type == sf::Event::KeyReleased)
			{
				button.play();
				menu.MoveDown();
			}

			//which menu option is selected using enter key
			if (menuScreen.key.code == sf::Keyboard::Return && menuScreen.type == sf::Event::KeyReleased)
				if (menu.getSelectedItemIndex() == 1)//"entered" play button
					playMenu = true;
				else if (menu.getSelectedItemIndex() == 2)//"entered" controls button
					controlMenu = true;
				else if (menu.getSelectedItemIndex() == 3)//"entered" exit button
					window.close();



			//mouse hovering the play button
			if ((mouseX > window.getSize().x* (.42) && mouseX < window.getSize().x * (.55)) &&
				((mouseY > window.getSize().y / 3.8) && (mouseY < window.getSize().y / 2.7)))
			{
				if (menu.getSelectedItemIndex() != 1)//prevents music spam
					button.play();

				menu.hoverSelected(1);
				if (menuScreen.type == sf::Event::MouseButtonReleased)//clicks the play button
					playMenu = true;

			}//hovering the controls button
			else if ((mouseX > window.getSize().x* (.38) && mouseX < window.getSize().x * (.62)) &&
				((mouseY > window.getSize().y / 2.6) && (mouseY < window.getSize().y / 2.05)))
			{
				if (menu.getSelectedItemIndex() != 2) //prevents music spam
					button.play();

				menu.hoverSelected(2);
				if (menuScreen.type == sf::Event::MouseButtonReleased)//clicks the control button
					controlMenu = true;

			}//hovering the exit button
			else if ((mouseX > window.getSize().x* (.43) && mouseX < window.getSize().x * (.55)) &&
				((mouseY > window.getSize().y / 2) && (mouseY < window.getSize().y / 1.63)))
			{
				if (menu.getSelectedItemIndex() != 3)//prevents music spam
					button.play();

				menu.hoverSelected(3);
				if (menuScreen.type == sf::Event::MouseButtonReleased)//clicks the exit button
					window.close();
			}


		}





		//NEW CHANGES HERE
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (playMenu == true) //Implement the main game here
		{




			//here is after the game ends it goes into the name input screen, and then into the gameover
			if(enterName)//NAMEINPUT SCREEN
			{
				if (menuScreen.type == sf::Event::TextEntered)

					nameInput.typedOn(menuScreen);
				


				//for mouse functionality
				if ((mouseX > window.getSize().x * .38 && mouseX < window.getSize().x * .63) &&
					(mouseY > window.getSize().y * .57 && mouseY < window.getSize().y * .66))
				{
					if (!nameInput.getContinueSelected())
						button.play();

					nameInput.hoverSelected(1);
					if (menuScreen.type == sf::Event::MouseButtonReleased)
					{
						enterName = false;

						//EXAMPLE ADDING A SCORE
						scores.addScore(60, nameInput.getName());
						gameover.addScoresToScreen(scores);
					}
				}
				else
					nameInput.hoverSelected(0);

				

				//for enter key functionality
				if (menuScreen.key.code == sf::Keyboard::Return && menuScreen.type == sf::Event::KeyReleased)
				{
					enterName = false;
					
					//EXAMPLE ADDING A SCORE
					scores.addScore(60, nameInput.getName());
					gameover.addScoresToScreen(scores);
				}


				window.clear();
				nameInput.draw(window);
				window.display();


			}
			
			
			if (!enterName){ //GAMEOVERSCREEN ONCE ENTERED PRESSED FOR NAME INPUT
				

				if ((mouseX > window.getSize().x * .35 && mouseX < window.getSize().x * .64) &&
					(mouseY > window.getSize().y * .8 && mouseY < window.getSize().y * .91))
				{
					if (!gameover.getSelectedExit())
						button.play();

					gameover.hoverSelected(1);
					if (menuScreen.type == sf::Event::MouseButtonReleased)
						window.close();
				}
				else
					gameover.hoverSelected(0);


				
				window.clear();
				gameover.draw(window);
				window.display();
			}
			
				
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





			//for the control menu
			if (controlMenu == true)
			{
				 if ( (mouseX < window.getSize().x/6.2) && (mouseY > window.getSize().y *(.85)) )
				 { 
					 if (controls.getSelectedBack() == false)
						 button.play();
					 
					 controls.hoverSelected(1);

					 if (menuScreen.type == sf::Event::MouseButtonReleased)
						 controlMenu = false;

				 }
				 else {
					 controls.hoverSelected(0);
				 }

				 if (menuScreen.key.code == sf::Keyboard::Left && menuScreen.type == sf::Event::KeyReleased)
				 {
					 controlMenu = false;
				 }

				 window.clear();
				 controls.draw(window);
				 window.display();

			}

			
			//not entirely sure why but i have to have this here as well to display the main menu without 
			//displaying a blank white screen every time
			if (playMenu == false && controlMenu == false)
			{
				window.clear();
				menu.draw(window);
				window.display();
			}


			//if window is closed
			if (menuScreen.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}


		}


		
	}


	return 1;


}