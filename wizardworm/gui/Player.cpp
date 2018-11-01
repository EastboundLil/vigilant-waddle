#include "stdafx.h"
#include "Player.h"
#include<vector>


Player::Player(sf::RenderWindow *w , std::string name)
{
	window = w;
	wizard = new Wizard(50,50,1, window);
	player_name = name;

}


Player::~Player()
{}

void Player::move(float x, float y,float deltaTime){
	
	wizard->move(x,y);
	wizard->wizAnimationUpdate(deltaTime);

}


void Player::draw() {

	wizard->draw();
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