#include "stdafx.h"
#include "Window.h"
#include "Animation.h"
#include "Button.h"
#include <iostream>

#include "ApplicationManager.h"


Window::Window()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "WizardWorm!");
	player =std::make_shared<Player>( window , "elsojatekos");

	spellBar = new SpellBar(350.0f,530.0f,window);
	fireBolt.loadFromFile("Gexp.png");
	laserBeam.loadFromFile("LaserBeamFragmentFull.png");

	//background.loadFromFile("background.jpg");
	background.loadFromFile("DonaldTrump.jpg");
	

	std::shared_ptr<MinorMap> round = std::make_shared<MinorMap>(100, 100, sf::Color(92, 51, 23, 255), 200, 400, window, 40, 40);
	round->make_me_round();

	map = std::make_unique<Map>(round , window);
	map->add_minormap(std::make_shared<MinorMap>(500, 100, sf::Color(92, 51, 23, 255), 160, 160, window, 50, 30));
	map->add_minormap(std::make_shared<MinorMap>(100, 300, sf::Color(92, 51, 23, 255), 160, 160, window, 10, 30));
}


Window::~Window()
{
	delete window;
	
	
}

void Window::mapeditor() {



	float deltaTime = 0.0f;
	sf::Clock clock;
	
	sf::Vector2i startpoint(-1, -1);
	sf::Vector2i endpoint;
	bool isdrag = false;
	



	Button* rectorroundselector=new Button(10.0f,10.0f,100.0f,100.0f,sf::Color::Black , "rect or round" , window, [this]() {
		if (rectorround) {
			rectorround = false;
		}
		else {
			rectorround = true;
		}
	});




	while (window->isOpen())
	{
		sf::Event event;
		sf::Vector2i pos;
		deltaTime = clock.restart().asSeconds();
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Blue);
		rect.setOutlineThickness(-2);


		while (window->pollEvent(event))
		{


			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{


				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{

					window->clear(sf::Color::Cyan);
					return;

				}

			}
			if (event.type == sf::Event::MouseButtonPressed)
			{


				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

					if (rectorroundselector->inside(sf::Mouse::getPosition(*window))) { rectorroundselector->make_action(); }
					
					if (!isdrag) {
						isdrag = true;
						startpoint = sf::Mouse::getPosition(*window);
						rect.setPosition(static_cast<float>(startpoint.x), static_cast<float>(startpoint.y));
					}
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					pos = sf::Mouse::getPosition(*window);
					isdrag = false;

					map->explosion_happened(pos);


				}
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

					sf::Vector2f s;
					sf::Vector2f e;
					if (startpoint.x <= endpoint.x) {
						s.x = static_cast<float>(startpoint.x);
						e.x = static_cast<float>(endpoint.x);
					}
					else {
						s.x = static_cast<float>(endpoint.x);
						e.x = static_cast<float>(startpoint.x);
					}

					if (startpoint.y <= endpoint.y) {
						s.y = static_cast<float>(startpoint.y);
						e.y = static_cast<float>(endpoint.y);
					}
					else {
						s.y = static_cast<float>(endpoint.y);
						e.y = static_cast<float>(startpoint.y);
					}
					std::cout << "mapadded,  kezdete:  " << s.x << " " << s.y << "mérete: " << e.x - s.x << " " << e.y - s.y << "\n";
					std::shared_ptr<MinorMap> newmap = std::make_shared<MinorMap>(s.x, s.y, sf::Color(92, 51, 23, 255), e.y - s.y, e.x - s.x, window, 30, 30);
					if(!rectorround)
						newmap->make_me_round();
					map->add_minormap(newmap);
					
					std::cout << "felengedtem a balt \n";
					isdrag = false;
				}
			}
		}



		endpoint = sf::Mouse::getPosition(*window);

		rect.setPosition(static_cast<float>(startpoint.x), static_cast<float>(startpoint.y));

		window->clear(sf::Color::Cyan);

		if (isdrag) {

			rect.setSize(sf::Vector2f(static_cast<float>(endpoint.x - startpoint.x), static_cast<float>(endpoint.y - startpoint.y)));
			window->draw(rect);
		}






		map->draw();

		rectorroundselector->draw();
		window->draw(rect);
		window->display();
	}

}




void Window::eventhandler() {

	//TODO Innen folyt. k�v. holnap
	//M�g �tt kell rakni hogy bizonyos pontban legyen a robban�s ---- spell hat�s�ra -- adott ideig


	float deltaTime = 0.0f;
	sf::Clock clock;
	float asd = 1;
	sf::CircleShape ellipse(200);
	ellipse.setScale(1, 1);
	ellipse.setPosition(100, 100);
	ellipse.setFillColor(sf::Color::Green);



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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) exit(0);
				/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					// move left...
					asd--;
					player->move(-1, 0, asd);
				}*/
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
				if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					ApplicationManager::getInstance().getEngineManager()->Move(sf::Keyboard::isKeyPressed(sf::Keyboard::Space), sf::Keyboard::isKeyPressed(sf::Keyboard::Left), sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					player->possible_shoot(0);
					spellBar->setSelected(1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					player->possible_shoot(1);
					spellBar->setSelected(2);
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
					window->clear(sf::Color::Cyan);
					mapeditor();
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				{

					map->load_from_file("map.txt");
				}


			}
			if (event.type == sf::Event::MouseButtonPressed)
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

					pos = sf::Mouse::getPosition(*window);

					if (1 == spellBar->getSelected()) {
						player->shoot(pos, fireBolt);
					}
					else {
						player->shoot(player->get_arrow()->get_deg(), laserBeam);
					}

					map->explosion_happened(pos);


				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {


					map->make_destructible(sf::Mouse::getPosition(*window));

				}
			}
		}



		player->shootUpdate(deltaTime);
		window->clear(sf::Color::Cyan);
		window->draw(sf::Sprite(background));

		map->draw();

		for (int i = 0; i < explosion_v.size(); i++) {			
			window->draw(*explosion_v[i]);
		}
		//text.setPosition(posx, posy);

		//for (int i = 0; i < player->getWizard_v().size(); i++) {
			player->set_Pos(ApplicationManager::getInstance().getEngineManager()->Find(player->getWizard_v()[0]), asd);
		//}
			player->set_Pos(ApplicationManager::getInstance().getEngineManager()->Find(player->getWizard_v()[1]), asd);

		player->draw();

		spellBar->draw();

		window->display();

	}
}

void Window::onTimerEndMsg()
{
	player->move(100, 0, 100);
}
