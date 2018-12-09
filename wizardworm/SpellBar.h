#pragma once

#include "Drawable.h"

class SpellBar : public Drawable {
	sf::RenderWindow* window;
	int selected;
	sf::Texture texture1;
	sf::RectangleShape fireBolt;
	sf::Texture texture2;
	sf::RectangleShape laserBeam;
	sf::RectangleShape selectedItem;

public:
	SpellBar(float x,float y,sf::RenderWindow *w);
	void setSelected(int select);
	void draw() override;

};