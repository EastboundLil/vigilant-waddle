#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "networking/INWManager.h"
#include "IWindow.h"
#include "Map.h"
#include "SpellBar.h"
#include "ApplicationManager.h"

class Window : public IWindow
{
	//std::unique_ptr<sf::RenderWindow> window;
	sf::RenderWindow *window;
	std::vector<std::shared_ptr<Player>> player_v;
	std::shared_ptr<Player> myplayer;
	std::shared_ptr<Map> map;

	SpellBar* spellBar;
	sf::Texture fireBolt;
	bool rectorround = true;
	bool solidordestr = true;
	sf::Texture laserBeam;
	sf::Texture background;

	void joinScreen();
	void hostScreen();

public:
	std::string line;


	void thegame() override;
	void mapeditor();
	void onTimerEndMsg();
	void startMenu() override;
	void mapSelector() override;

	void receiveMap(std::stringstream& map);

	void textEdit(sf::Event event,std::string &s);

	std::shared_ptr<Map> get_map();

	Window();
	~Window();
};

