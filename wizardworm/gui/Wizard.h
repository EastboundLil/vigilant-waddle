#pragma once

#include <SFML/Graphics.hpp>
#include "Bar.h"
#include "Animation.h"
#include "Arrow.h"
#include "Block.h"



class Wizard : public Drawable
{
protected:
	int id;
	std::string name;

	int X_OFFSET = 0;
	float width = 50;
	float height = 40;
	
	Bar* lifebar;
	Bar* manabar;
	Arrow* arrow;
	std::vector<Arrow*> arrow_v;
	sf::RenderWindow* window;		
	sf::Texture texture;
	sf::RectangleShape wormImage;
	float deltaTime;
	Animation *animation;

public:
	Wizard(float x_ , float y_ , float id_ ,sf::RenderWindow* window,std::string image_name);
	~Wizard();
	void draw();
	void move(float x, float y , float deltatime);
	void set_Pos(sf::Vector2f pos );
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
	void wizAnimationUpdate();
	int get_id();
	std::string curr_spell();
	bool point_in_wizard(sf::Vector2f p);
	//TODO Bence vagyok elbasztam csinaltam egy egyszerubb megoldast mert most azt nezem hogy a blokk pontjai benne vannak e wizardban de ha tul nagy a blokk akkor a ket pontja koze a wizard beesik plusz  annyira egy fasz vagyok hogy nem a sarkan fog menni hanem a lejton szoval leszopok mindenkit egy sorert (komment vissza)
	bool wizard_in_block(std::shared_ptr<Block> b);
	bool wizard_in_shape(sf::ConvexShape s);

};

