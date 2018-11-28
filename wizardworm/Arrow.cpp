#include "Arrow.h"

#include <iostream>

 Arrow::Arrow()
{
	

}

Arrow::Arrow(float _x, float _y , sf::RenderWindow * w , std::string t) :  Drawable(_x, _y) {
	
	deg = mind;
	force = minf;
	opened = false;
	type = t;
	if (t == "firebolt") {
		rect.setFillColor(sf::Color(205, 51, 51, 200));
	}
	else if (t == "laserbeam") {
		rect.setFillColor(sf::Color::Magenta);
	}
	rect.setSize(sf::Vector2f(100 * force, 10));
	rect.setOrigin(0, 5);
	rect.setRotation(deg);
	
	window = w;
	std::cout << "elso force: " << force << "\n";
}


Arrow::~Arrow()
{
}

void Arrow::draw()
{

	if (opened) {

		rect.setRotation(deg);
		rect.setPosition(x, y);
		window->draw(rect);
		
	}
}

bool Arrow::is_opened()
{
	return opened;
}

void Arrow::set_opened(bool t)
{
	
		opened = t;
	
	std::cout << "arrow: " << opened << "\n";
}

void Arrow::incr_deg(float a)
{
	if (deg + a > maxd) {
		deg = fmod(deg + a, maxd)+mind;
	}
	else if (deg + a < mind) {
		deg = maxd + fmod(deg + a , maxd);
	}
	else {
		deg += a;
	}
	rect.setRotation(deg);
}

void Arrow::incr_force(float a)
{
	if (force + a > maxf) {
		force = fmod(force + a, maxf) + minf;
	}
	else if (force + a < minf) {
		force = maxf + fmod(force + a, maxf);
	}
	else {
		force += a;
	}
	std::cout <<force <<" \n";
	rect.setSize(sf::Vector2f(force * 100, 10));
}

std::string Arrow::get_type()
{
	return type;
}

float Arrow::get_deg()
{
	return deg;
}

float Arrow::get_force()
{
	return force;
}

float Arrow::mind = 0;
float Arrow::minf = 0.1f;
float Arrow::maxd = 360;
float Arrow::maxf = 1.0f;