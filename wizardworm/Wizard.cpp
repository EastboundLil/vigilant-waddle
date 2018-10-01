#include "stdafx.h"
#include "Wizard.h"



Wizard::Wizard(sf::RenderWindow *w)
{
	set_value(1); //�l e m�g a var�zsl� 
	set_position(100, 100); //Var�zsl� kezdeti poz�ci�ja
	window = w;
	life = new Properties(window); //A var�zsl� �lete
	mana = new Properties(window); //A var�zsl� man�ja
	life->set_position(100, 100 - 25);
	mana->set_position(100, 100 - 20);

}


Wizard::~Wizard(){}


void Wizard::draw() {

	sf::Texture texture;
	if (!texture.loadFromFile("WizardWorm.png")) {
	
		system("pause");
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(get_position().get_x(), get_position().get_y());
	//Worm nagys�ga
	sprite.setScale(0.30, 0.30);


	/*sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(10, 25));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(get_position().get_x(), get_position().get_y());*/
	
	window->draw(sprite);
	

	//TODO att� f�gg�en milyen sz�nre �ll�tod m�s az x poz�ci�ja
		//Faszs�g
	life->draw(sf::Color::Red);
	mana->draw(sf::Color::Blue);
}

void Wizard::move_to(int x,int y) {
	//Az �let �s a mana elheyez�s�nek be�ll�t�sa + sz�nek

	move(x, y);
	life->move(x, y);
	mana->move(x, y);

}

