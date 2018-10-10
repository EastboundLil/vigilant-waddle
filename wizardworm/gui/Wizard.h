#pragma once

#include <SFML/Graphics.hpp>
#include "Bar.h"





class Wizard : public Drawable
{
protected:
	Bar* lifebar;
	Bar* manabar;
	sf::RenderWindow* window;
	
public:
	Wizard(float x_ , float y_ , float id_ ,sf::RenderWindow* window);
	~Wizard();
	void draw();
	void move(float x, float y);
	void set_life(float l);
	void set_mana(float m);
	void incr_life(float l);
	void incr_mana(float m);
	void wiz_shoot(std::string spell_type);

};

