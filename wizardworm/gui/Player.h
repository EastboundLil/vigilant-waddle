#pragma once
#include "Firebolt.h"
#include <vector>
#include "Wizard.h"

//TODO Egy J�t�kosnak t�bb var�zsl� kell melyeket �l�n kezel

class Player
{

	Wizard* wizard;
	sf::RenderWindow *window;
	std::string player_name;
	std::vector<Spell*> livingspells;

public:

	Player(sf::RenderWindow* w, std::string name);
	~Player();
	
	void move(float x, float y);
	void draw() ;
	void shoot(std::string spell_type);

};

