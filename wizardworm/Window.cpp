#include "stdafx.h"
#include "Window.h"
#include <iostream>

Window::Window()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "WizardWorm!");
	player = new Player(window , "elsojatekos");
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) /*&& not mouse event*/)
			{
				// move left...
				player->move(-1,0);
				std::cout << "balra" << std::endl;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)/*&& not mouse event*/)
			{
				// move right...
				
				player->move(1,0);
				std::cout << "jobbra" << std::endl;
			}
		}
		window->clear(sf::Color::Black);
		//window.draw(rectangle);
		player->draw();
		window->display();
	}

}
