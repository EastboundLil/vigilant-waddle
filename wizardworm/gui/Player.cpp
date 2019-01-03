#include "stdafx.h"
#include "Player.h"
#include<vector>
#include <iostream>

Player::Player(sf::RenderWindow *w , std::string name)
{
	window = w;
	
	wizardvector.push_back(new Wizard(50,200,0, window));
	wizardvector.push_back(new Wizard(100, 50, 1, window));
	wizard = wizardvector[0];
	player_name = name;

}


Player::~Player()
{
	wizardvector.clear();
}

void Player::move(float x, float y,float deltaTime){
	
	
	wizard->move(x,y,deltaTime);
	//wizard->wizAnimationUpdate(deltaTime);

}

void Player::set_Pos(sf::Vector2f pos )
{
	wizard->set_Pos(pos );
	
	//wizard->wizAnimationUpdate(deltaTime);
}

std::vector<Wizard*> Player::getWizard_v()
{
	return wizardvector;
}


Wizard* Player::getWizard() {
	return wizard;
}

void Player::draw() {
	for (Wizard* w : wizardvector) {
		w->draw();
	}
	
	for (size_t i = 0; i < livingspells.size();i++) {
		if(livingspells[i]->getIsLive())
			livingspells[i]->draw();
		else {
			//TODO erase helyett lehet nem ártana más
			Spell* temp = livingspells[i];
			livingspells.erase(livingspells.begin() + i);
			delete temp;
		}
	}
}

void Player::shoot(sf::Vector2i mousePos, sf::Texture &texture) {

	livingspells.push_back(new Firebolt(window, sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)), texture));
	wizard->incr_mana(-livingspells.back()->get_mana_cost());
}

void Player::shoot(float deg, sf::Texture &texture) {
	livingspells.push_back(new LaserBeam(window,sf::Vector2f(wizard->get_x(),wizard->get_y()),deg, texture));
	wizard->incr_mana(-livingspells.back()->get_mana_cost());

}

/*void Player::shoot()
{
	Arrow* a = wizard->get_arrow();
	if (a!=nullptr) {
		float d = a->get_deg();
		float f = a->get_force();
		std::string type = a->get_type();
		
		float rx = 20;
		float ry = rx * tan(d) - (pow(rx, 2)*9.8) / (2 * pow(f * 100, 2)*pow(cos(d), 2));
		//TODO: livingspells.push_back(new Firebolt(window, sf::Vector2f(a->get_x , a->get_y) , d , f));
		std::cout << "robbanas: " << rx << " " << ry <<"f: "<<f*100<<"d:"<<d<< "\n";
		livingspells.push_back(new Firebolt(window, sf::Vector2f(rx*10+ a->get_x(), -ry+ a->get_y())));
		
		livingspells.push_back(new Firebolt(window, sf::Vector2f(200, 200)));
		wizard->incr_mana(-livingspells.back()->get_mana_cost());
	}
}*/

void Player::shootUpdate(float deltaTime) {

	for (Spell* s : livingspells) {
		s->updateAnimation(deltaTime);
	}

}

void Player::possible_shoot(int i)
{

	wizard->change_curr_arrow(i);
	
	std::cout << "arrow nyilik \n";
	//TODO: manabaron mutassa a costot
	
}



void Player::switch_wizard()
{
	wizard->close_arrow();
	if (wizard->get_id() + 1 >= wizardvector.size()) {
		wizard = wizardvector[0];
	}
	else {
		wizard = wizardvector[wizard->get_id() + 1];
	}
	wizard->open_arrow();

}

void Player::switch_wizard(int i)
{
	if (i >= 0 && i < wizardvector.size()) {
		wizard = wizardvector[i];
	}
}

void Player::aim(bool up)
{
	wizard->wizaim(up);	
}

void Player::changeforce()
{
	wizard->wizforce();
}

Arrow* Player::get_arrow() {
	return wizard->get_arrow();
}

int Player::getWizardsVectSize() {
	return wizardvector.size();
}

Wizard* Player::getWizard(int i) {
	return wizardvector[i];
}