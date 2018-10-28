#include "Spell.h"





Spell::Spell()
{
	spellImage.setSize(sf::Vector2f(100.0f, 100.0f));
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

void Spell::updateAnimation(float deltaTime) {
	animation->Update(deltaTime);
	spellImage.setTextureRect(animation->uvRect);
}