#include "Button.h"


#include <iostream>


Button::Button(float posx, float posy, float width , float height ,sf::Color color, std::string t, sf::RenderWindow *w ,std::function<bool()> action)
	: Drawable(posx , posy, color)  , width(width) , height(height), action(action) , window(w)
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
	text.setCharacterSize(2*width/t.size());

	if (!font.loadFromFile("Roboto-Regular.ttf")) {
		std::cout << "szar afajl  \n";
	}
	else {
		std::cout << "jó a fajl \n";
		text.setFont(font);
	}
}

void Button::change_shape(bool t) {
	shapechooser = t;
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
	change_shape(action());
	
}

void Button::draw() {

	if (shapechooser) {
		window->draw(rect);
	}
	else {
		window->draw(circle);
	}
	
	
	text.setFont(font);
	
	window->draw(text);

}
