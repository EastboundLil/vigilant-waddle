#include "stdafx.h"
#include "Player.h"


Player::Player(sf::RenderWindow *w)
{
	window = w;
	wizard = new Wizard(window);

}


Player::~Player()
{}

void Player::move(int x,int y){ 

	wizard->move_to(x,y);

}

void Player::draw() {

	wizard->draw();
}
