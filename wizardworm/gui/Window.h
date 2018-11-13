#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Block.h"
#include "networking/INWManager.h"
#include "IWindow.h"

class Window : public IWindow
{
	std::shared_ptr<INWManager> networkManager;

	//std::unique_ptr<sf::RenderWindow> window;
	sf::RenderWindow *window;
	std::shared_ptr<Player> player;
	std::vector<std::unique_ptr<Block>> map; // it will be a class based on engine 

public:

	void eventhandler() override;

	void onTimerEndMsg();

	Window();
	~Window();
};

