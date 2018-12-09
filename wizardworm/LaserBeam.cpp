#include "LaserBeam.h"
#include <iostream>


LaserBeam::LaserBeam(sf::RenderWindow *window,sf::Vector2f pos,float deg, sf::Texture &texture)
{
	mana_cost = 10;
	damage = 15;
	x = pos.x;
	y = pos.y;
	this->window = window;

	texture.setSmooth(true);
	
	spellImage.setTexture(&texture);
	animation = new Animation(&texture, sf::Vector2u(1, 20), 0.1f);

	spellImage.setSize(sf::Vector2f(1000.0f, 130.0f));
	spellImage.setOrigin(sf::Vector2f(0.0f, spellImage.getSize().y*0.5));
	spellImage.rotate(deg);


	//LaserBeamImage.setRadius(100);
	//LaserBeamImage.setOutlineColor(sf::Color::Red);

	//this->x_pos=x_pos;
	//this->y_pos = y_pos;
	//LaserBeamImage.setPosition(x_pos, y_pos);

}

LaserBeam::LaserBeam(const LaserBeam& f) : Spell(f.mana_cost , f.damage) {
	
}

LaserBeam::~LaserBeam()
{
}


void LaserBeam:: draw() {
	//std::cout << "rajzolok egy fireballt \n";
	spellImage.setPosition(x+50.0f, y+30.0f);
	window->draw(spellImage);
}
