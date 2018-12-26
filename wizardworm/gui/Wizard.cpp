#include "stdafx.h"
#include "Wizard.h"
#include "Animation.h"


#include<iostream>
#include<vector>


Wizard::Wizard(float x_ , float y_ , float _id , sf::RenderWindow *w)
	:Drawable(x_, y_)
{
	//set_value(1); //�l e m�g a var�zsl� 
	set_pos(x_ , y_ ); //Var�zsl� kezdeti poz�ci�ja
	window = w;
	
	lifebar = new Bar(x_,y_-25 , sf::Color::Red ,50 , window); //A var�zsl� �lete
	manabar = new Bar(x_, y_-20 , sf::Color::Blue , 50 , window); //A var�zsl� man�ja
	arrow_v.push_back( new Arrow(x_ + 47, y_ + 21, window , "firebolt"));
	arrow_v.push_back( new Arrow(x_ + 47, y_ + 21, window, "laserbeam"));
	arrow = arrow_v[0];
	id = _id;
	texture.loadFromFile("WormsAnimation.png");
	texture.setSmooth(true);

	wormImage.setSize(sf::Vector2f(100.0f, 100.0f));
	wormImage.setTexture(&texture);
	animation = new Animation(&texture, sf::Vector2u(4, 2), 10);

	wormImage.setPosition(x_, y_);
	wormImage.setScale(0.50f, 0.50f);
	wormImage.setTextureRect(animation->uvRect);
	deltaTime = 2.f;
	wizAnimationUpdate();
	wizAnimationUpdate();
	wizAnimationUpdate();

}


Wizard::~Wizard(){
	delete lifebar;
	delete manabar;
	delete animation;
}


void Wizard::draw() {

	wormImage.setPosition(x+X_OFFSET, y);
	window->draw(wormImage);
	
	lifebar->draw();
	manabar->draw();
	if (arrow != nullptr) {
		arrow->draw();
	}

}

void Wizard::set_Pos(sf::Vector2f pos ) {
	if ((pos.x ) > this->x)
	{
		X_OFFSET = 0;
		wormImage.setScale(0.50f, 0.50f);
	}
	else if(pos.x<this->x)
	{
		X_OFFSET = 50;
		wormImage.setScale(-0.50f, 0.50f);
	}

	if (pos.x != this->x || pos.y != this->y) {
		this->wizAnimationUpdate();
	
		

			set_pos(pos.x, pos.y);

			for (Arrow * a : arrow_v) {
				a->set_pos(x + 47, y + 21);
			}

			lifebar->set_pos(x, y - 25);
			manabar->set_pos(x, y - 20);
		
	}




}

void Wizard::move(float x, float y , float deltatime) {

	if ((x + this->x) > this->x)
	{
		X_OFFSET = 0;
		wormImage.setScale(0.50f, 0.50f);
	}
	else
	{	
		X_OFFSET = 50;
		wormImage.setScale(-0.50f, 0.50f);
	}

	if (this->x != x) {
		wizAnimationUpdate();
		incr_pos(x, y);

		for (Arrow * a : arrow_v) {
			a->incr_pos(x, y);
		}

		lifebar->incr_pos(x, y);
		manabar->incr_pos(x, y);
	}
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

Arrow* Wizard::get_arrow() {

	
	if (arrow->is_opened() ) {

		return arrow;
	}
	return nullptr;

}

void Wizard::open_arrow()
{
	std::cout << arrow->get_type() << "kinyit \n";
	arrow->set_opened(true);
}

void Wizard::close_arrow()
{
	std::cout << arrow->get_type() << "bezár \n";
	arrow->set_opened(false);
}

void Wizard::change_arrow_opening()
{
	if (arrow->is_opened()) {
		
		close_arrow();
	}
	else {
		
		open_arrow();
	}
}

void Wizard::change_curr_arrow(int i)
{
	
	if (i>=0 && i<arrow_v.size()) {
		
		if ((i == 0 && arrow->get_type() == "firebolt") || (i == 1 && arrow->get_type() == "laserbeam")) {
			change_arrow_opening();
			return;
		}
		arrow = arrow_v[i];
		arrow->set_opened(false);
		arrow = arrow_v[i];
		arrow->set_opened(true);

		
		
		
		
	}
}



void Wizard::wizaim(bool up)
{
	if (arrow->is_opened()) {
		if (up) {
			arrow->incr_deg(-10);
		}
		else {
			arrow->incr_deg(10);
		}

	}
}

void Wizard::wizforce()
{
	if (arrow->is_opened()) {	
		
			arrow->incr_force(0.05f);	

	}
	
	
}

void Wizard::wizAnimationUpdate() {

	animation->Update(deltaTime++);
	wormImage.setTextureRect(animation->uvRect);
}

int Wizard::get_id() {
	return id;
}

std::string Wizard::curr_spell()
{

	return std::string();
}

bool Wizard::point_in_wizard(sf::Vector2f p)
{
	return p.x>this->x && p.x<this->x+this->width && p.y>this->y && p.y < this->y + this->height;
}

bool Wizard::wizard_in_block(std::shared_ptr<Block> b)
{
	//alja
	if (b->check_bound(sf::Vector2f(this->x+width/2, this->y + height))) {
		if (b->contains(sf::Vector2f(this->x + width/2, this->y + height)))
			return true;
	}

	//jobbja
	if (b->check_bound(sf::Vector2f(this->x+width, this->y + height / 2))) {
		if (b->contains(sf::Vector2f(this->x+width, this->y + height / 2)))
			return true;
	}

	//balja
	if (b->check_bound(sf::Vector2f(this->x, this->y + height / 2))) {
		if(b->contains(sf::Vector2f(this->x, this->y + height / 2)))
			return true;
	}

	//teteje
	if (b->check_bound(sf::Vector2f(this->x+width/2, this->y))) {
		if (b->contains(sf::Vector2f(this->x+width/2, this->y)))
			return true;
	}

	
	return false;
}
