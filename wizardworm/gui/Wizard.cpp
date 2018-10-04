#include "stdafx.h"
#include "Wizard.h"


#include<iostream>
#include<vector>


Wizard::Wizard(float x_ , float y_ , float id , sf::RenderWindow *w)
	:Drawable(x_, y_)
{
	//set_value(1); //�l e m�g a var�zsl� 
	set_pos(x_ , y_ ); //Var�zsl� kezdeti poz�ci�ja
	window = w;
	lifebar = new Bar(x_,y_-25 , sf::Color::Red ,50 , window); //A var�zsl� �lete
	manabar = new Bar(x_, y_-20 , sf::Color::Blue , 50 , window); //A var�zsl� man�ja
	

	

}


Wizard::~Wizard(){
	delete lifebar;
	delete manabar;
	
}


void Wizard::draw() {

	sf::Texture texture;
	if (!texture.loadFromFile("WizardWorm.png")) {
	
		system("pause");
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	//Worm nagys�ga
	sprite.setScale(0.30f, 0.30f);

	//ha kép helyett worm kéne:
	/*sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(10, 25));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(get_position().get_x(), get_position().get_y());*/
	
	window->draw(sprite);
	

	//TODO att� f�gg�en milyen sz�nre �ll�tod m�s az x poz�ci�ja
		//Faszs�g
	lifebar->draw();
	manabar->draw();
}

void Wizard::move(float x, float y) {
	//Az �let �s a mana elheyez�s�nek be�ll�t�sa + sz�nek

	incr_pos(x, y);
	lifebar->incr_pos(x, y);
	manabar->incr_pos(x, y);

}

void Wizard::set_life(float l)
{
	//TODO: catchelni kell az exceptiont
	
	lifebar->set_val(l);

}

void Wizard::set_mana(float m)
{
	//TODO: catchelni kell az exceptiont
	manabar->set_val(m);
}

void Wizard::incr_life(float l)
{
	//TODO: catchelni kell az exceptiont
	lifebar->incr_val(l);
}

void Wizard::incr_mana(float m)
{
	//TODO: catchelni kell az exceptiont
	manabar->incr_val(m);
}

void Wizard::wiz_shoot(std::string spell_type) {

	
	
	
	if (spell_type == "firebolt") {
		std::cout << "lottem egy fireboltot \n";
		
	}
	else if (spell_type == "laserbeam") {
		std::cout << "lottem egy laserbeamet \n";
	}

}

