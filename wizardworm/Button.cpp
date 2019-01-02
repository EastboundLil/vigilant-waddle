#include "Button.h"


#include <iostream>


Button::Button(float posx, float posy, float width , float height ,sf::Color color, std::string t1 ,sf::RenderWindow *w ,std::function<bool()> action)
	: Drawable(posx , posy, color)  , width(width) , height(height), action(action) , window(w) , t(t1)
{
	
	rect.setFillColor(color);
	rect.setPosition(posx, posy);
	rect.setSize(sf::Vector2f(width, height));
	
	circle.setFillColor(color);
	circle.setPosition(posx, posy);
	circle.setRadius(fmin(width/2, height/2));
	circle.setScale(width / height, 1);

	text.setString(t);
	text.setPosition(posx, posy);
	text.setFillColor(sf::Color::White);
	//text.setCharacterSize(2*width/t.size());

	if (!font.loadFromFile("Roboto-Regular.ttf")) {
		std::cout << "rossz afajl  \n";
	}
	else {
		//std::cout << "jó a fajl \n";
		text.setFont(font);
	}
}



bool Button::inside(sf::Vector2i click)
{
	return click.x<x+width && click.x>x && click.y>y && click.y<y+height;
}

void Button::set_action(std::function<bool()> a)
{
	action = a;
}

Button::~Button()
{
}

void Button::make_action() {
	action();
	
}

void Button::draw() {

	
	window->draw(rect);

	text.setFont(font);

	window->draw(text);

}
