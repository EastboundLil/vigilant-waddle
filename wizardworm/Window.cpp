#include "stdafx.h"
#include "Window.h"
#include <iostream>

Window::Window()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "WizardWorm!");
	player = new Player(window);
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// move left...
				player->set_wizard_position(-1);
				std::cout << "balra" << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				// move right...
				player->set_wizard_position(1);
				std::cout << "jobbra" << std::endl;
			}
		}

		window->clear(sf::Color::Black);
		//window.draw(rectangle);
		player->draw();
		window->display();
	}

}
