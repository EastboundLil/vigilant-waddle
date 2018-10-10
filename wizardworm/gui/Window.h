#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

#include "networking/INWManager.h"
#include "IWindow.h"

class Window : public IWindow
{
	INWManager* networkManager;

	sf::RenderWindow *window;
	Player *player;

public:

	void eventhandler() override;

	void onTimerEndMsg();

	Window();
	Window(INWManager* nwManager);
	~Window();
};

