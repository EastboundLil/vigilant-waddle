#pragma once
#include "Drawable.h"
#include <SFML/Graphics.hpp>

class Bar :
	public Drawable
{
protected:
	float full_val;
	float curr_val;
		sf::Color missing_color;
		sf::RenderWindow *window;

		sf::RectangleShape missingrectangle;
		sf::RectangleShape currentrectangle;



public:
	Bar(float x_ , float y_ , sf::Color c_ , float init_val, sf::RenderWindow *w);
	~Bar();

	void set_val(float v);
	void incr_val(float v);
	void draw() override;
	
};