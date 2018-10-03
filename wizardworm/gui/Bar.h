#pragma once
#include "Drawable.h"
#include <SFML/Graphics.hpp>

class Bar :
	public Drawable
{
protected:
		int full_val;
		int curr_val;
		sf::RenderWindow *window;



public:
	Bar(int x_ , int y_ , sf::Color c_ , int init_val, sf::RenderWindow *w);
	~Bar();

	void set_val(int v);
	void incr_val(int v);
	void draw();
	
};