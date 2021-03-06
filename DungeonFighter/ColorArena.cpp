// DungeonFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include <SFML\Graphics.hpp>

using namespace sf;

int main()
{
	enum class State
	{
		PAUSED, LEVELING_UP, GAME_OVER, PLAYING
	};


	//Start with the GAME_OVER state
	State state = State::GAME_OVER;

	//Get the screen resolution and create SFML windows
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Color Arena", Style::Fullscreen);

	//Create a an SFML View for main action
	View mainView(FloatRect(0, 0, resolution.x, resolution.y));

	//Here is clock for timing everything
	Clock clock;

	//How long has has PLAYING state benn active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;

	// Where is the mouse in relation to world screen
	Vector2i mouseScreenPosition;

	//Create a instance of Player class
	Player player;

	//The boundaries of the arena
	IntRect arena;

	//The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handling Input
		************
		*/

		// handle event
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				//Pause a game while playing
				if (event.key.code == Keyboard::Return && state == State::PLAYING)
				{
					state = State::PAUSED;
				}

				//Restart while paused
				else if (event.key.code == Keyboard::Return && state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't frame jump
					clock.restart();
				}

				//Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}
				if (state == State::PLAYING)
				{
				}
			}
		}//End of pollEvent


	//Handling the player quitting the game
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//Handle control while playing
		if (state == State::PLAYING)
		{
			//Handling the pressing and releasing of teh WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
		}//End of WASD while playing

		//Handling the leveling up state
		if (state == State::LEVELING_UP)
		{
			//Handle the player leveling
			if (event.key.code == Keyboard::Num1)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num2)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5)
			{
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6)
			{
				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{
				//Prepare the level
				//We will modifythe next two lines later
				arena.width = 100;
				arena.height = 100;
				arena.left = 0;
				arena.top = 0;

				//we will modify this line later
				int tileSize = 50;

				//Spawn the player in the middle arena
				player.spawn(arena, resolution, tileSize);

				//Reset the clock so there isn't frame jump
				clock.restart();
			}//End of leveling
		}

		/*
		*************
		Update Frame
		**************
		*/
		if (state == State::PLAYING) 
		{
			//Update teh delta time
			Time dt = clock.restart();
			//Update the total game time
			gameTimeTotal += dt;
			//Made a decimal fraction of 1 fromthe delta time
			float dtAsSeconds = dt.asSeconds();

			//Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			//Convert mouse position to world coordination of mainView
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

			//Update the player
			player.update(dtAsSeconds, Mouse::getPosition());

			//Make note of the player new position
			Vector2f playerPosition(player.getCenter());

			//Make the center view around the player
			mainView.setCenter(player.getCenter());
		}//End of the updating frame

		/*
		****************
		Draw scene
		*************
		*/

		if (state == State::PLAYING)
		{
			window.clear();
			//set the mainVIew to be displayed in the windows
			//And draw everythingrelated to it
			window.setView(mainView);

			//Draw player
			window.draw(player.getSprite());
		}
		if (state == State::LEVELING_UP)
		{
		}
		if (state == State::GAME_OVER)
		{
		}
		if (state == State::PAUSED)
		{
		}
		
		window.display();


	}
	return 0;
}

