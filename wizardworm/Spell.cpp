#include "Spell.h"





Spell::Spell()
{
	

}


Spell::~Spell()
{
}

float Spell::get_mana_cost()
{
	return mana_cost;
}

float Spell::get_damage()
{
	return damage;
}

Spell::Spell(float m, float d) {
	mana_cost = m;
	damage = d;
}

