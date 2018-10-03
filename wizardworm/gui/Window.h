#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Window
{

	sf::RenderWindow *window;
	Player *player;

public:

	void eventhandler();

	Window();
	~Window();
};

