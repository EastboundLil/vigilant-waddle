#pragma once
#include "Properties.h"
#include <SFML/Graphics.hpp>

class Wizard :public Properties
{
	Properties* life;
	Properties* mana;
	sf::RenderWindow* window;
public:
	Wizard(sf::RenderWindow* window);
	~Wizard();
	void draw();

};

