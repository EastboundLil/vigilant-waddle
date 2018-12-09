#pragma once
#include "Firebolt.h"
#include "LaserBeam.h"
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
	//void shoot(std::string spell_type,sf::Vector2i mousePos,float deg,sf::Texture &texture);
	void shoot(sf::Vector2i mousePos,sf::Texture &texture);
	void shoot(float deg,sf::Texture &texture);
	//void shoot();
	void shootUpdate(float deltaTime);
	void possible_shoot(int i);
	void switch_wizard();
	void switch_wizard(int i);
	void aim(bool up);
	void changeforce();

	Arrow* get_arrow();

};

