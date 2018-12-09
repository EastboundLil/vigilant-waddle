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
	std::unique_ptr<Map> map;

	SpellBar* spellBar;
	sf::Texture fireBolt;
	bool rectorround = true;
	sf::Texture laserBeam;
	sf::Texture background;


public:

	void eventhandler() override;
	void mapeditor();
	void onTimerEndMsg();
	void startMenu() override;

	Window();
	~Window();
};

