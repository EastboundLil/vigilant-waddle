#include "stdafx.h"
#include "Window.h"
#include "Animation.h"
#include "ChangeButton.h"
#include <iostream>
#include "ApplicationManager.h"
#include "Logger.h"

Window::Window()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "WizardWorm!");
	player_v.push_back( std::make_shared<Player>( window , "elsojatekos"));

	spellBar = new SpellBar(350.0f,530.0f,window);
	fireBolt.loadFromFile("Gexp.png");
	laserBeam.loadFromFile("LaserBeamFragmentFull.png");

	background.loadFromFile("background.jpg");
	//background.loadFromFile("DonaldTrump.jpg");
	
	
	//std::shared_ptr<MinorMap> round = std::make_shared<MinorMap>(100, 100, sf::Color(92, 51, 23, 255), 200, 400, window, 40, 40);
	//round->make_me_round();

	map = std::make_shared<Map>( window);
	//map->load_from_file("map.txt");
	//map->add_minormap(std::make_shared<MinorMap>(500, 100, sf::Color(92, 51, 23, 255), 160, 160, window, 50, 30));
	//map->add_minormap(std::make_shared<MinorMap>(100, 300, sf::Color(92, 51, 23, 255), 160, 160, window, 10, 30));


	

}


Window::~Window()
{
	delete window;
	
	
}

void Window::mapeditor() {



	float deltaTime = 0.0f;
	sf::Clock clock;
	map->make_empty();
	sf::Vector2i startpoint(-1, -1);
	sf::Vector2i endpoint;
	bool isdrag = false;
	std::vector<Button*> button_v;
	rectorround = true;
	solidordestr = true;
	ChangeButton *rectorroundselector = new ChangeButton(10.0f, 10.0f, 100.0f, 25.0f, sf::Color::Black, sf::Color::Black,"   add  rectangle  " ," add ellipse ", window, [this]() ->bool{
		if (rectorround) {
			rectorround = false;
			return false;
		}
		else {
			rectorround = true;
			return true;
		}


	});

	button_v.push_back(rectorroundselector);

	ChangeButton *solidordestrselector = new ChangeButton(10.0f, 50.0f, 200.0f, 50.0f, sf::Color::Black, sf::Color(92, 51, 23, 255), " make solid  ", " make destructible ", window, [this]() ->bool {
		if (solidordestr) {
			solidordestr = false;
			return false;
		}
		else {
			solidordestr = true;
			return true;
		}


	});
	button_v.push_back(solidordestrselector);

	Button *addnewmapbutton = new Button(200 , 10 , 200 ,50 , sf::Color::Black , "save this map" , window , [this]() ->bool {
		
		map->write_data_to_file("map.txt");
		return true;
	});

	button_v.push_back(addnewmapbutton);
	//TODO: soliddestructiblebutton
	


	




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

				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{

					window->clear(sf::Color::Cyan);
					return;

				}
				
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				{

					map->load_from_file("map.txt");
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (solidordestr) {
						map->make_solid(sf::Mouse::getPosition(*window));
					}
					else {
					
						map->make_destructible(sf::Mouse::getPosition(*window));
					}
				}
				

			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

					if (rectorroundselector->inside(sf::Mouse::getPosition(*window))) { rectorroundselector->make_action(); }
					if (solidordestrselector->inside(sf::Mouse::getPosition(*window))) { solidordestrselector->make_action(); }
					if (!isdrag) {
						isdrag = true;
						startpoint = sf::Mouse::getPosition(*window);
						rect.setPosition(static_cast<float>(startpoint.x), static_cast<float>(startpoint.y));
					}
					if (addnewmapbutton->inside(sf::Mouse::getPosition(*window)))
					{
						addnewmapbutton->make_action();
						std::cout << "\n megnyomtak a savemapot \n";
					}
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					pos = sf::Mouse::getPosition(*window);
					isdrag = false;

					map->explosion_happened(pos , 50);


				}
			}

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && isdrag) {
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
					if (e.x != s.x && e.y != s.y) {
						std::cout << "mapadded,  kezdete:  " << s.x << " " << s.y << "mérete: " << e.x - s.x << " " << e.y - s.y << "\n";
						std::shared_ptr<MinorMap> newminormap = std::make_shared<MinorMap>(s.x, s.y, sf::Color(92, 51, 23, 255), e.y - s.y, e.x - s.x, window, 30, 30);
						if (!rectorround)
							newminormap->make_me_round();
						if (solidordestr)
							newminormap->make_solid();
						map->add_minormap(newminormap);
					}
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



		for (int i = 0; i < button_v.size(); i++) {
		
			button_v[i]->draw();

		}


		map->draw();

		rectorroundselector->draw();
		window->draw(rect);
		window->display();
	}
	button_v.clear();
}




void Window::eventhandler() {
	ApplicationManager::getInstance().getEngineManager()->AddPlayer(player_v[0]->getWizard_v());
	float deltaTime = 0.0f;
	sf::Clock clock;
	float asd = 1;
	sf::CircleShape ellipse(200);
	ellipse.setScale(1, 1);
	ellipse.setPosition(100, 100);
	ellipse.setFillColor(sf::Color::Green);
	map->load_from_file("map.txt");

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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return;
				/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					// move left...
					asd--;
					player->move(-1, 0, asd);
				}*/
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					//arrow degree up;
					player_v[0]->aim(true);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					//arrow degree up;
					player_v[0]->aim(false);
				}
				if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					player_v[0]->getWizard()->close_arrow();
					ApplicationManager::getInstance().getEngineManager()->Move(sf::Keyboard::isKeyPressed(sf::Keyboard::Space), sf::Keyboard::isKeyPressed(sf::Keyboard::Left), sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
					
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					player_v[0]->possible_shoot(0);
					spellBar->setSelected(1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					player_v[0]->possible_shoot(1);
					spellBar->setSelected(2);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
					ApplicationManager::getInstance().getEngineManager()->Switch();
					player_v[0]->switch_wizard();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					//arrow degree up;
					player_v[0]->changeforce();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					window->clear(sf::Color::Cyan);
					mapeditor();
				}
				
				


			}
			if (event.type == sf::Event::MouseButtonPressed)
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

					pos = sf::Mouse::getPosition(*window);

					if (player_v[0]->get_arrow() != nullptr) {
						if (1 == spellBar->getSelected()) {
							player_v[0]->shoot(pos, fireBolt);
							map->explosion_happened(pos, 50);
						}
						else {
							float deg = player_v[0]->get_arrow()->get_deg();
							player_v[0]->shoot(deg, laserBeam);
							//std::cout << deg << "deg" << std::endl;
							map->laserExp_happened(sf::Vector2i(player_v[0]->getWizard()->get_x(), player_v[0]->getWizard()->get_y()),player_v, deg);
						}
					}


				}
				
			}
		}



		player_v[0]->shootUpdate(deltaTime);
		window->clear(sf::Color::Cyan);
		window->draw(sf::Sprite(background));

		map->draw();

		for (int i = 0; i < explosion_v.size(); i++) {			
			window->draw(*explosion_v[i]);
		}
		

		for (int i = 0; i < player_v[0]->getWizard_v().size(); i++) {
			//std::cout << "asd: " << asd << "\n";
			player_v[0]->set_Pos(ApplicationManager::getInstance().getEngineManager()->Find(player_v[0]->getWizard()));
		}
			

		player_v[0]->draw();

		spellBar->draw();



		window->display();

	}
}

void Window::onTimerEndMsg()
{
	player_v[0]->move(100, 0, 100);
}


void Window::startMenu()
{
	Button *joinGame = new Button(50.0f, 50.0f, 200.0f, 50.0f, sf::Color::Green, "Join Game", window, [this]()->bool {joinScreen();  return true; });
	Button *createGame = new Button(50.0f, 115.0f, 200.0f, 50.0f, sf::Color::Green, "Create Game", window, [this]()->bool {eventhandler(); return true; });
	Button *createMap = new Button(50.0f, 175.0f, 200.0f, 50.0f, sf::Color::Green, "Create Map", window, [this]()->bool {mapeditor(); return true; });
	Button *exitGame = new Button(50.0f, 235.0f, 200.0f, 50.0f, sf::Color::Green, "Exit Game", window, [this]()->bool {window->close(); return true; });
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) eventhandler();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (joinGame->inside(sf::Mouse::getPosition(*window))) { joinGame->make_action(); }
					if (createGame->inside(sf::Mouse::getPosition(*window))) { createGame->make_action(); }
					if (createMap->inside(sf::Mouse::getPosition(*window))) { createMap->make_action(); }
					if (exitGame->inside(sf::Mouse::getPosition(*window))) { exitGame->make_action(); }
				}
			}

			window->draw(sf::Sprite(background));

			joinGame->draw();
			createGame->draw();
			createMap->draw();
			exitGame->draw();
			
			window->display();
		}
	}
}

void Window::mapSelector()
{



	//TODO: itt kell egy kivalaszto widget, meg egy lista ami tartalmazza a létező mapokat, vagy egy lehetőség hogy új mapot csinálj, plusz, minden map mellé hogy map kiprobalasa
	while (window->isOpen())
	{


		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return;
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					
				}
			}

			window->draw(sf::Sprite(background));

			

			window->display();
		}
	}

}

void Window::joinScreen()
{
	ApplicationManager::getInstance().getNetworkManager()->stopNetworking();
	ApplicationManager::getInstance().getNetworkManager()->startAsClient();

	sf::Text text;
	text.setString(sf::String("Ip address:"));
	text.setPosition(50, 50);

	while (window->isOpen() || ApplicationManager::getInstance().getNetworkManager()->getNetworkStatus() != sf::Socket::Status::Done)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return;
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				}
			}

			ApplicationManager::getInstance().getNetworkManager()->setRemoteAddress("127.0.0.1");
			ApplicationManager::getInstance().getNetworkManager()->startConnection();

			window->draw(sf::Sprite(background));
			window->draw(text);

			window->display();
		}
	}
}

void Window::hostScreen()
{
	ApplicationManager::getInstance().getNetworkManager()->stopNetworking();
	ApplicationManager::getInstance().getNetworkManager()->startAsServer();

	while (window->isOpen() || ApplicationManager::getInstance().getNetworkManager()->getNetworkStatus() != sf::Socket::Status::Done)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return;
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				}
			}

			window->draw(sf::Sprite(background));

			window->display();
		}
	}
}

std::shared_ptr<Map> Window::get_map()
{
	return map;
}
