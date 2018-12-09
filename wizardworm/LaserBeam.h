#pragma once
#include "Spell.h"

class LaserBeam :public Spell {
	sf::RenderWindow *window;
	float x_pos;
	float y_pos;
	sf::CircleShape LaserBeamImage;


public:
	LaserBeam(sf::RenderWindow *window,sf::Vector2f pos, float deg, sf::Texture &texture);
	LaserBeam(const LaserBeam& f);
	//TODO: Firebolt(sf::RenderWindow *windom, sf::Vector2f startpos , float deg , float force);
	~LaserBeam();
	void draw() override;
};

