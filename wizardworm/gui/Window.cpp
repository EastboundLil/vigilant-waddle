#include "stdafx.h"
#include "Window.h"
#include <iostream>

#include "ApplicationManager.h"

Window::Window()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "WizardWorm!");
	player = new Player(window , "elsojatekos");

	networkManager = ApplicationManager::getInstance().getNetworkManager();
}


Window::~Window()
{
}

void Window::eventhandler() {


	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed) {
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					// move left...
					player->move(-1, 0);
					std::cout << "balra" << std::endl;
				}
				else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					// move right...

					player->move(1, 0);
					std::cout << "jobbra" << std::endl;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					player->shoot("firebolt");
				}
			}
			
		}
		window->clear(sf::Color::Black);
		//window.draw(rectangle);
		player->draw();
		window->display();
	}

}

void Window::onTimerEndMsg()
{
	player->move(100, 0);
}
