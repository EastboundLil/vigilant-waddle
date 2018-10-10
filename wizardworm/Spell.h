#pragma once



class Spell {
protected:
	float mana_cost;
	float damage;
	


public:
	
	 Spell();
	 Spell(float m, float d);
	~Spell();
	virtual void draw() = 0;
	float get_mana_cost();
	float get_damage();
};

