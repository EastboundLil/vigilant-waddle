#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Block.h"
#include "networking/INWManager.h"
#include "IWindow.h"

class Window : public IWindow
{
	std::shared_ptr<INWManager> networkManager;

	sf::RenderWindow *window;
	Player *player;
	std::vector<Block *> map; // it will be a class based on engine 

public:

	void eventhandler() override;

	void onTimerEndMsg();

	Window();
	~Window();
};

