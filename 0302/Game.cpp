#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"




void Game::start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(512, 384, 32), "Gaem");
	_gameState = Game::ShowingSplash;

	_tileManager.load();

	_camera_x = 0;
	_camera_y = 0;


	//TEST:

	while (!isExiting())
	{
		gameLoop();
	}

	_mainWindow.close();
}

bool Game::isExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::gameLoop()
{



	switch (_gameState)
	{
		case Game::ShowingMenu:
		{
			showMenu();
			break;
		}
		case Game::ShowingSplash:
		{
			showSplashScreen();
			break;
		}
		case Game::Playing:
		{
			float xvel = 0;
			float yvel = 0;

			sf::Event currentEvent;
			while (_mainWindow.isOpen())
			{
				

				// game logic here
				_camera_x += xvel;
				_camera_y += yvel;


				_mainWindow.clear(sf::Color(0, 0, 0));

				// draw everything here:

				// layer 0 (tiles)
				_tileManager.draw(_camera_x, _camera_y, _mainWindow);



				_mainWindow.display();


				// events
				while (_mainWindow.pollEvent(currentEvent))
				{
					if (currentEvent.type == sf::Event::Closed)
					{
						_gameState = Game::Exiting;
						_mainWindow.close();
						break;
					}
					else if (currentEvent.type == sf::Event::KeyPressed)
					{
						switch (currentEvent.key.code)
						{
							case sf::Keyboard::Escape:
							{
								showMenu();
								break;
							}
							case sf::Keyboard::W:
							{
								yvel = -1;
								break;
							}
							case sf::Keyboard::A:
							{
								xvel = -1;
								break;
							}
							case sf::Keyboard::S:
							{
								yvel = 1;
								break;
							}
							case sf::Keyboard::D:
							{
								xvel = 1;
								break;
							}
							default:
							{
								break;
							}
						}

					}
					else if (currentEvent.type == sf::Event::KeyReleased)
					{
						switch (currentEvent.key.code)
						{
							case sf::Keyboard::W:
							{
								yvel = 0;
								break;
							}
							case sf::Keyboard::A:
							{
								xvel = 0;
								break;
							}
							case sf::Keyboard::S:
							{
								yvel = 0;
								break;
							}
							case sf::Keyboard::D:
							{
								xvel = 0;
								break;
							}
							default:
							{
								break;
							}
						}
					}
				}
			}
			break;
		}
	}
}

void Game::showSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.show(_mainWindow);
	_gameState = Game::ShowingMenu;

}

void Game::showMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.show(_mainWindow);
	switch (result)
	{
		case MainMenu::Exit:
		{
			_gameState = Game::Exiting;
			break;
		}
		case MainMenu::Play:
		{
			_gameState = Game::Playing;
			break;
		}
	}
}

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
TileManager Game::_tileManager;
float Game::_camera_x;
float Game::_camera_y;