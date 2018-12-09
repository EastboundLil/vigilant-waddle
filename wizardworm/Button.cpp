#include "Button.h"


#include <iostream>


Button::Button(float posx, float posy, float width , float height ,sf::Color color, std::string t, sf::RenderWindow *w ,std::function<void()> action)
	: Drawable(posx , posy, color)  , width(width) , height(height), action(action) , window(w)
{
	rect.setFillColor(color);
	rect.setPosition(posx, posy);
	rect.setSize(sf::Vector2f(width, height));
	text.setString(t);
	text.setPosition(posx, posy);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(15);
	sf::Font f;
	if (!f.loadFromFile("font.ttf")) {
		std::cout << "szar afajl  \n";
	}
	text.setFont(f);
	
}

bool Button::inside(sf::Vector2i click)
{
	return click.x<x+width && click.x>x && click.y>y && click.y<y+height;
}

void Button::set_action(std::function<void()> a)
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
	window->draw(text);


}
