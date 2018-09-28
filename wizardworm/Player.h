#pragma once

#include "Properties.h"
#include "Wizard.h"

//TODO Egy Játékosnak több varázsló kell melyeket ülön kezel

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

