#include "stdafx.h"
#include "Player.h"
#include<vector>


Player::Player(sf::RenderWindow *w , std::string name)
{
	window = w;
	wizard = new Wizard(100,100,1, window);
	player_name = name;

}


Player::~Player()
{}

void Player::move(float x, float y){
	
	wizard->move(x,y);

}

void Player::draw() {

	wizard->draw();
	for (Spell* s : livingspells) {
		s->draw();
	}
}

void Player::shoot(std::string spell_type) {

	
	livingspells.push_back(new Firebolt());
	wizard->incr_mana(-livingspells.back()->get_mana_cost());
}