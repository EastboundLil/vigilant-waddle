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
	
	void set_wizard_position(int val);
	void draw();

};

