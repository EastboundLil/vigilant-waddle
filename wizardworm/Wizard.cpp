#include "stdafx.h"
#include "Wizard.h"



Wizard::Wizard(sf::RenderWindow *w)
{
	set_value(1); //Él e még a varázsló 
	set_position(100, 100); //Varázsló kezdeti pozíciója
	window = w;
	life = new Properties(window); //A varázsló élete
	mana = new Properties(window); //A varázsló manája
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
	//Worm nagysága
	sprite.setScale(0.30, 0.30);


	/*sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(10, 25));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(get_position().get_x(), get_position().get_y());*/
	
	window->draw(sprite);
	

	//TODO attó függõen milyen színre állítod más az x pozíciója
		//Faszság
	life->draw(sf::Color::Red);
	mana->draw(sf::Color::Blue);
}

void Wizard::move_to(int x,int y) {
	//Az élet és a mana elheyezésének beállítása + színek

	move(x, y);
	life->move(x, y);
	mana->move(x, y);

}

