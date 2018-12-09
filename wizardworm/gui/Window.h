#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "networking/INWManager.h"
#include "IWindow.h"
#include "Map.h"
#include "SpellBar.h"


class Window : public IWindow
{
	std::shared_ptr<INWManager> networkManager;
	std::shared_ptr<IEngine> engineManager;

	//std::unique_ptr<sf::RenderWindow> window;
	sf::RenderWindow *window;
	std::shared_ptr<Player> player;
	std::unique_ptr<Map> map;

	SpellBar* spellBar;
	sf::Texture fireBolt;
	sf::Texture background;

public:

	void eventhandler() override;
	void mapeditor();
	void onTimerEndMsg();

	Window();
	~Window();
};

