#pragma once
#include "Drawable.h"
#include "Animation.h"


class Spell : public Drawable {
protected:
	float mana_cost;
	float damage;
	Animation *animation;
	sf::Texture texture;
	sf::RectangleShape spellImage;


public:
	
	 Spell();
	 Spell(float m, float d);
	~Spell();
	virtual void draw() = 0;
	void updateAnimation(float deltaTime);
	float get_mana_cost();
	float get_damage();

	bool getIsLive() { return animation->getIsLive(); }
};

