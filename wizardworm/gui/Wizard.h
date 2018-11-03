#pragma once

#include <SFML/Graphics.hpp>
#include "Bar.h"
#include "Animation.h"
#include "Arrow.h"




class Wizard : public Drawable
{
protected:
	int id;
	std::string name;
	
	Bar* lifebar;
	Bar* manabar;
	Arrow* arrow;

	sf::RenderWindow* window;		
	sf::Texture texture;
	sf::RectangleShape wormImage;

	Animation *animation;

public:
	Wizard(float x_ , float y_ , float id_ ,sf::RenderWindow* window);
	~Wizard();
	void draw();
	void move(float x, float y);
	void set_life(float l);
	void set_mana(float m);
	void incr_life(float l);
	void incr_mana(float m);
	void wiz_shoot(std::string spell_type);
	void open_arrow();
	void close_arrow();
	void change_arrow();
	void wizaim(bool up);
	void wizforce();
	void wizAnimationUpdate(float deltaTime);
	int get_id();

};

