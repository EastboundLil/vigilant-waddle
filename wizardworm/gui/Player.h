#pragma once
#include "Firebolt.h"

#include <vector>
#include "Wizard.h"
#include "LaserBeam.h"

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
	void set_Pos(sf::Vector2f pos , float deltaTime);
	std::vector<Wizard*> getWizard_v();
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
	Wizard* getWizard();
	sf::Vector2i getPosition() { return sf::Vector2i(wizard->get_x(), wizard->get_y()); };

	Arrow* get_arrow();

};

