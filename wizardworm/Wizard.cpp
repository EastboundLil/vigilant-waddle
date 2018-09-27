#include "stdafx.h"
#include "Wizard.h"



Wizard::Wizard(sf::RenderWindow *w)
{
	set_value(1); //Él e még a varázsló 
	set_position(100, 100); //Varázsló kezdeti pozíció
	window = w;
	life = new Properties(window); //A varázsló élete
	mana = new Properties(window); //A varázsló manája

}


Wizard::~Wizard(){}

void Wizard::draw() {
	//TODO ki kell majd cserélni képre
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(10, 25));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(get_position().get_x(), get_position().get_y());
	
	window->draw(rectangle);
	
	//Az élet és a mana elheyezésének beállítása + színek
	life->set_position(get_position().get_x(), get_position().get_y() - 25);
	mana->set_position(get_position().get_x(), get_position().get_y() -20);
	
	life->draw(sf::Color::Red);
	mana->draw(sf::Color::Blue);
}

