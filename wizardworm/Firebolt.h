#pragma once
#include "Spell.h"

class Firebolt :public Spell{
	sf::RenderWindow *window;
	float x_pos;
	float y_pos;
	sf::CircleShape FireboltImage;
	


public:
	Firebolt(sf::RenderWindow *window, sf::Vector2i mousePos) ;
	Firebolt(const Firebolt& f);

	~Firebolt();
	void draw() override;
};

