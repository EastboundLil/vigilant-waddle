#pragma once

#include "Properties.h"
#include "Wizard.h"

//TODO Egy J�t�kosnak t�bb var�zsl� kell melyeket �l�n kezel

class Player
{

	Wizard* wizard;
	sf::RenderWindow *window;

public:

	Player(sf::RenderWindow* w);
	~Player();
	
	void move(int x, int y);
	void draw();

};

