#include "SpellBar.h"

SpellBar::SpellBar(float x_,float y_,sf::RenderWindow *w):Drawable(x_,y_) {
	selected = 1;
	window = w;
	texture1.loadFromFile("FireBolt.jpg");
	texture2.loadFromFile("LaserBeam.jpg");
	
	fireBolt.setSize(sf::Vector2f(50.0f, 50.0f));
	laserBeam.setSize(sf::Vector2f(50.0f, 50.0f));
	selectedItem.setSize(sf::Vector2f(60.0f, 60.0f));
	selectedItem.setFillColor(sf::Color::Blue);

	fireBolt.setTexture(&texture1);
	laserBeam.setTexture(&texture2);

	fireBolt.setPosition(x_, y_);
	laserBeam.setPosition(x_+60, y_);

	selectedItem.setPosition(x_-5, y_-5);
}

void SpellBar::draw() {

	if (selected == 1) {
		selectedItem.setPosition(fireBolt.getPosition().x-5, fireBolt.getPosition().y - 5);
	}
	else {
		selectedItem.setPosition(laserBeam.getPosition().x-5, laserBeam.getPosition().y - 5);
	}
	window->draw(selectedItem);
	window->draw(fireBolt);
	window->draw(laserBeam);
}

void SpellBar::setSelected(int select) {
	selected = select;
}