#pragma once
#include "Spell.h"

class Firebolt :
	public Spell
{
	sf::RenderWindow *window;

	//sf::RectangleShape FireboltImage;


public:
	Firebolt(sf::RenderWindow *window, sf::Vector2i mousePos) ;
	Firebolt(const Firebolt& f);

	~Firebolt();
	void draw() override;
};

