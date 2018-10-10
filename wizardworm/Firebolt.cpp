#include "Firebolt.h"
#include <iostream>


Firebolt::Firebolt() 
{
	mana_cost = 20;
	damage = 30;
	
}

Firebolt::Firebolt(const Firebolt& f) : Spell(f.mana_cost , f.damage) {
	

}

Firebolt::~Firebolt()
{
}

void Firebolt:: draw() {
	//std::cout << "rajzolok egy fireballt \n";
	
}
