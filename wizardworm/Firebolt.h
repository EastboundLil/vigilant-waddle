#pragma once
#include "Spell.h"

class Firebolt :
	public Spell
{
public:
	Firebolt() ;
	Firebolt(const Firebolt& f);

	~Firebolt();
	void draw() override;
};

