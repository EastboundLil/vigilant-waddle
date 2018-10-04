#include "stdafx.h"
#include "Player.h"


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
}

void Player::shoot(std::string spell_type) {

	wizard->wiz_shoot(spell_type);

}