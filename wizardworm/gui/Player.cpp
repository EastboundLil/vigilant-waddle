#include "stdafx.h"
#include "Player.h"
#include<vector>


Player::Player(sf::RenderWindow *w , std::string name)
{
	window = w;
	
	wizardvector.push_back(new Wizard(50,50,0, window));
	wizardvector.push_back(new Wizard(100, 50, 1, window));
	wizard = wizardvector[0];
	player_name = name;

}


Player::~Player()
{
	wizardvector.clear();
}

void Player::move(float x, float y,float deltaTime){
	
	wizard->close_arrow();
	wizard->move(x,y);
	wizard->wizAnimationUpdate(deltaTime);

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

			livingspells.erase(livingspells.begin() + i);
		}
	}
}

void Player::shoot(std::string spell_type,sf::Vector2i mousePos) {

	
	livingspells.push_back(new Firebolt(window,mousePos));
	wizard->incr_mana(-livingspells.back()->get_mana_cost());
}

void Player::shootUpdate(float deltaTime) {

	for (Spell* s : livingspells) {
		s->updateAnimation(deltaTime);
	}

}

void Player::possible_firebolt_shoot()
{
	wizard->change_arrow();
	//TODO: legyen a wizardnak egy nyilja, ami egy szögértéket tárol, azt lehet módosítani a nyilakkal, ha a nyil->isopened igaz.
	//TODO: manabaron mutassa a costot
	//TODO: nyíl letrehozása amit nyilakkal lehet mozgatni
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
