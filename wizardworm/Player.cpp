#include "stdafx.h"
#include "Player.h"


Player::Player(sf::RenderWindow *w)
{
	window = w;
	wizard = new Wizard(window);

}


Player::~Player()
{}

void Player::set_wizard_position(int val){ 

	wizard->move(val,0);

}

void Player::draw() {

	wizard->draw();
}
