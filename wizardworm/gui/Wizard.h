#pragma once

#include <SFML/Graphics.hpp>
#include "Bar.h"

class Wizard :public Drawable
{
protected:
	Bar* lifebar;
	Bar* manabar;
	sf::RenderWindow* window;
public:
	Wizard(int x_ , int y_ , int id_ ,sf::RenderWindow* window);
	~Wizard();
	void draw();
	void move(int x,int y);
	void set_life(int l);
	void set_mana(int m);
	void incr_life(int l);
	void incr_mana(int m);

};

