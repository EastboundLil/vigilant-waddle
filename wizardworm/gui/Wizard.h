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
	std::vector<Arrow*> arrow_v;
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
	Arrow* get_arrow();
	void open_arrow();
	void close_arrow();
	void change_arrow_opening();
	void change_curr_arrow(int i);
	void wizaim(bool up);
	void wizforce();
	void wizAnimationUpdate(float deltaTime);
	int get_id();
	std::string curr_spell();

};

