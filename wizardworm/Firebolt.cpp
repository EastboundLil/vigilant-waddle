#include "Firebolt.h"
#include <iostream>


Firebolt::Firebolt(sf::RenderWindow *window, sf::Vector2i mousePos)
{
	mana_cost = 20;
	damage = 30;
	this->window = window;
	texture.loadFromFile("Gexp.png");
	texture.setSmooth(true);
	spellImage.setTexture(&texture);
	animation = new Animation(&texture, sf::Vector2u(4, 2), 0.15f);


	spellImage.setPosition(mousePos.x-50.0f,mousePos.y-54.375f);

}

Firebolt::Firebolt(const Firebolt& f) : Spell(f.mana_cost , f.damage) {
	

}

Firebolt::~Firebolt()
{
}

void Firebolt:: draw() {
	//std::cout << "rajzolok egy fireballt \n";
	window->draw(spellImage);
}
