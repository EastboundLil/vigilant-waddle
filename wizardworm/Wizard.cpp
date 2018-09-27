#include "stdafx.h"
#include "Wizard.h"



Wizard::Wizard(sf::RenderWindow *w)
{
	set_value(1); //�l e m�g a var�zsl� 
	set_position(100, 100); //Var�zsl� kezdeti poz�ci�
	window = w;
	life = new Properties(window); //A var�zsl� �lete
	mana = new Properties(window); //A var�zsl� man�ja

}


Wizard::~Wizard(){}

void Wizard::draw() {
	//TODO ki kell majd cser�lni k�pre
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(10, 25));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(get_position().get_x(), get_position().get_y());
	
	window->draw(rectangle);
	
	//Az �let �s a mana elheyez�s�nek be�ll�t�sa + sz�nek
	life->set_position(get_position().get_x(), get_position().get_y() - 25);
	mana->set_position(get_position().get_x(), get_position().get_y() -20);
	
	life->draw(sf::Color::Red);
	mana->draw(sf::Color::Blue);
}

