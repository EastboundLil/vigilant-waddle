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

	map.push_back(new Block(100, 100, sf::Color::Green, 100, 100, window));
	map.push_back(new Block(200, 100, sf::Color::Green, 100, 100, window));
	map.push_back(new Block(300, 100, sf::Color::Green, 100, 100, window));
	map.push_back(new Block(100, 200, sf::Color::Green, 100, 100, window));
	map.push_back(new Block(200, 200, sf::Color::Green, 100, 100, window));
	map.push_back(new Block(300, 200, sf::Color::Green, 100, 100, window));
	map.push_back(new Block(100, 300, sf::Color::Green, 100, 100, window));
	map.push_back(new Block(200, 300, sf::Color::Green, 100, 100, window));
	map.push_back(new Block(300, 300, sf::Color::Green, 100, 100, window));
}


Window::~Window()
{
	delete window;
	delete player;
	map.clear();
}

void Window::eventhandler() {

	//TODO Innen folyt. köv. holnap
	//Még átt kell rakni hogy bizonyos pontban legyen a robbanás ---- spell hatására -- adott ideig

	float deltaTime = 0.0f;
	sf::Clock clock;
	float asd = 1;


	
	/*sf::RectangleShape teszt(sf::Vector2f(100.0f,100.0f));
	sf::Texture texture;
	texture.loadFromFile("WormsAnimation.png");
	texture.setSmooth(true);
	teszt.setTexture(&texture);
	Animation animation(&texture, sf::Vector2u(4, 2), 0.15f);
	*/
	std::vector<sf::CircleShape*> explosion_v;
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
					player->shoot();
				}

			}
			if (event.type == sf::Event::MouseButtonPressed)
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

					sf::Vector2i pos = sf::Mouse::getPosition(*window);

					player->shoot("Firebolt", pos);
					//ezt most valamiert nem rajzolja ki
					explosion_v.push_back(new sf::CircleShape());
					explosion_v[explosion_v.size() - 1]->setRadius(100.0f);
					explosion_v[explosion_v.size() - 1]->setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
					explosion_v[explosion_v.size() - 1]->setOrigin(100.0f, 100.0f);
					explosion_v[explosion_v.size() - 1]->setFillColor(sf::Color::Transparent);
					explosion_v[explosion_v.size() - 1]->setOutlineColor(sf::Color::Red);
					explosion_v[explosion_v.size() - 1]->setOutlineThickness(-2);

					for (int i = 0; i < map.size(); i++) {
						if (map[i]->caught_by_expl(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
							std::cout << i << "-ik elem modosul \n";
						}
					}
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				
					explosion_v.clear();
					map.clear();

					map.push_back(new Block(100, 100, sf::Color::Green, 100, 100, window));
					map.push_back(new Block(200, 100, sf::Color::Green, 100, 100, window));
					map.push_back(new Block(300, 100, sf::Color::Green, 100, 100, window));
					map.push_back(new Block(100, 200, sf::Color::Green, 100, 100, window));
					map.push_back(new Block(200, 200, sf::Color::Green, 100, 100, window));
					map.push_back(new Block(300, 200, sf::Color::Green, 100, 100, window));
					map.push_back(new Block(100, 300, sf::Color::Green, 100, 100, window));
					map.push_back(new Block(200, 300, sf::Color::Green, 100, 100, window));
					map.push_back(new Block(300, 300, sf::Color::Green, 100, 100, window));
				}
			}
		}


		//TODO õket is
		/*animation.Update(deltaTime);
		teszt.setTextureRect(animation.uvRect);*/
		
		player->shootUpdate(deltaTime);
		window->clear(sf::Color::Cyan);
		//window.draw(rectangle);
		
		//window->draw(teszt);
		for (int i = 0; i < map.size(); i++) {
			map[i]->draw();
		}
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
