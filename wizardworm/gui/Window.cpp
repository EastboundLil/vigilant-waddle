#include "stdafx.h"
#include "Window.h"
#include "Animation.h"
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

	//TODO Innen folyt. köv. holnap
	//Még átt kell rakni hogy bizonyos pontban legyen a robbanás ---- spell hatására -- adott ideig

	float deltaTime = 0.0f;
	sf::Clock clock;

	sf::RectangleShape teszt(sf::Vector2f(100.0f,100.0f));

	sf::Texture texture;
	texture.loadFromFile("Gexp.png");
	texture.setSmooth(true);
	teszt.setTexture(&texture);
	Animation animation(&texture, sf::Vector2u(4, 2), 0.15f);


	while (window->isOpen())
	{
		sf::Event event;
		deltaTime = clock.restart().asSeconds();


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


		//TODO õket is
		animation.Update(deltaTime);
		teszt.setTextureRect(animation.uvRect);
		

		window->clear(sf::Color::Cyan);
		//window.draw(rectangle);
		window->draw(teszt);
		player->draw();
		window->display();
	}

}

void Window::onTimerEndMsg()
{
	player->move(100, 0);
}
