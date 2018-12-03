#include "stdafx.h"
#include "Window.h"
#include "Animation.h"
#include <iostream>

#include "ApplicationManager.h"

Window::Window()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "WizardWorm!");
	player =std::make_shared<Player>( window , "elsojatekos");

	networkManager = ApplicationManager::getInstance().getNetworkManager();

	map = std::make_unique<Map>(100, 100, sf::Color(92, 51, 23, 255), 400, 400, window , 50 , 50);
}


Window::~Window()
{
	delete window;
	
	
}


void Window::eventhandler() {

	//TODO Innen folyt. k�v. holnap
	//M�g �tt kell rakni hogy bizonyos pontban legyen a robban�s ---- spell hat�s�ra -- adott ideig


	float deltaTime = 0.0f;
	sf::Clock clock;
	float asd = 1;



	std::vector<std::unique_ptr<sf::CircleShape>> explosion_v;
	while (window->isOpen())
	{
		sf::Event event;
		sf::Vector2i pos;
		deltaTime = clock.restart().asSeconds();
		
		while (window->pollEvent(event))
		{


			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed) {
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					// move left...
					asd++;
					player->move(-1, 0, asd);
					std::cout << "balra" <<asd <<std::endl;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					//arrow degree up;
					player->aim(true);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					//arrow degree up;
					player->aim(false);
				}
				else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					// move right...
					asd++;
					player->move(1, 0, asd);
					std::cout << "jobbra" <<asd<< std::endl;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					player->possible_shoot(0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					player->possible_shoot(1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					player->switch_wizard();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					//arrow degree up;
					player->changeforce();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					//arrow degree up;
					map->write_data();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{
					//arrow degree up;
					map->write_data_to_file("map.txt");
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					
					map->make_solid(sf::Mouse::getPosition(*window));
				}

				
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

					pos = sf::Mouse::getPosition(*window);
					player->shoot("Firebolt", pos);


					//ezt most valamiert nem rajzolja ki
					/*explosion_v.push_back(std::make_unique<sf::CircleShape>());
					explosion_v[explosion_v.size() - 1]->setRadius(100.0f);
					explosion_v[explosion_v.size() - 1]->setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
					explosion_v[explosion_v.size() - 1]->setOrigin(100.0f, 100.0f);
					explosion_v[explosion_v.size() - 1]->setFillColor(sf::Color::Transparent);
					explosion_v[explosion_v.size() - 1]->setOutlineColor(sf::Color::Red);
					explosion_v[explosion_v.size() - 1]->setOutlineThickness(-2);*/
					
								map->explosion_happened(pos);
								
					
					
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				
					//explosion_v.clear();
					//map = std::make_unique<Map>(100, 100, sf::Color(92, 51, 23, 255), 410, 430, window);
					//map->load_from_file("map.txt");
					map->make_destructible(sf::Mouse::getPosition(*window));
	
				}
			}
		}


		//TODO �ket is
		/*animation.Update(deltaTime);
		teszt.setTextureRect(animation.uvRect);*/
		
		player->shootUpdate(deltaTime);
		window->clear(sf::Color::Cyan);
		//window.draw(rectangle);
		

		//window->draw(teszt);
		map->draw();

		for (int i = 0; i < explosion_v.size(); i++) {
			
			window->draw(*explosion_v[i]);
		}
		
		player->draw();
		window->display();
	}

}

void Window::onTimerEndMsg()
{
	player->move(100, 0, 100);
}
