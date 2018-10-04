#pragma once
#include "Drawable.h"


class Spell :
	public Drawable
{
protected:
	float mana_cost;
	float damage;
	


public:
	
	 Spell();
	 Spell(float m, float d);
	~Spell();

};

