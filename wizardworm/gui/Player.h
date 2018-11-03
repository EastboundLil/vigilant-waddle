#pragma once
#include "Firebolt.h"
#include <vector>
#include "Wizard.h"

//TODO Egy J�t�kosnak t�bb var�zsl� kell melyeket �l�n kezel

class Player
{

	std::vector<Wizard*> wizardvector;
	Wizard* wizard;
	sf::RenderWindow *window;
	std::string player_name;
	std::vector<Spell*> livingspells;

public:

	Player(sf::RenderWindow* w, std::string name);
	~Player();
	
	void move(float x, float y, float deltaTime);
	void draw() ;
	void shoot(std::string spell_type,sf::Vector2i mousePos);
	void shootUpdate(float deltaTime);
	void possible_firebolt_shoot();
	void switch_wizard();
	void switch_wizard(int i);
	void aim(bool up);
	void changeforce();

};

