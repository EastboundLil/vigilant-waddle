#include "stdafx.h"
#include "Bar.h"


Bar::Bar(float x_, float y_ , sf::Color c_ , float init_val , sf::RenderWindow *w)
	:Drawable(x_, y_, c_)
{
	full_val  = init_val;
	curr_val = init_val;
	window = w;
	missing_color = c_;
	missing_color.a += -200;

	missingrectangle.setSize(sf::Vector2f(full_val, 5));
	currentrectangle.setSize(sf::Vector2f(curr_val, 5));
	missingrectangle.setFillColor(missing_color);

	currentrectangle.setFillColor(color);

}


Bar::~Bar()
{
}

void Bar::set_val(float v)
{
	if (v > full_val) {
		curr_val = full_val;
	
	}else if( v <= 0) {
		//TODO throw halál exception most még hallhatatlan
		curr_val = 1;

	}
	else {
		curr_val = v;
	}
	currentrectangle.setSize(sf::Vector2f(curr_val, 5));
}

void Bar::incr_val(float v)
{
	if (curr_val + v > full_val) {
		curr_val = full_val;
	} else if(  curr_val + v <= 0) {
	//TODO throw halál exception most még hallhatatlan
		curr_val = 1;
	}
	else {

		curr_val += v;
	}
	currentrectangle.setSize(sf::Vector2f(curr_val, 5));
}

void Bar::draw()
{
	

	
	missingrectangle.setPosition(x, y);	
	currentrectangle.setPosition(x, y);	
	
	window->draw(missingrectangle);
	window->draw(currentrectangle);
}