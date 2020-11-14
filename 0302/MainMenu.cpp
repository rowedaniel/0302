#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window)
{

	//Load menu image from file
	sf::Texture texture;
	if (texture.loadFromFile("images/MainMenu.bmp") != true)
	{
		// error
		std::cout << "AHHHHHH" << std::endl;
	}
	sf::Sprite sprite(texture);

	//Setup clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.left = 50;
	playButton.rect.width = 160;
	playButton.rect.top = 47;
	playButton.rect.height = 72;
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 63;
	exitButton.rect.width = 315;
	exitButton.rect.top = 283;
	exitButton.rect.height = 70;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return getMenuResponse(window);
}

MainMenu::MenuResult MainMenu::handleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.height+menuItemRect.top > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.width+menuItemRect.left > x)
		{
			return (*it).action;
		}
	}

	return Nothing;
}

MainMenu::MenuResult  MainMenu::getMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{

		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}