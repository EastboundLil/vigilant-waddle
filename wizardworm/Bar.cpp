#include "stdafx.h"
#include "Bar.h"


Bar::Bar(int x_, int y_ , sf::Color c_ , int init_val , sf::RenderWindow *w)
	:Drawable(x_, y_, c_)
{
	full_val = curr_val = init_val;
	window = w;
}


Bar::~Bar()
{
}

void Bar::set_val(int v)
{
	if ( v > full_val || v <= 0) {
		//TODO throw halál exception

	}
	else {
		curr_val = v;
	}
}

void Bar::incr_val(int v)
{
	if (curr_val+v > full_val || curr_val+v <= 0) {
	//TODO throw halál exception
		
	}
	else {
		curr_val += v;
	}
}

void Bar::draw()
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(curr_val , 5));
	rectangle.setFillColor(color);
	rectangle.setPosition(x,y);
	window->draw(rectangle);
}