#pragma once
#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include <vector>
#include <bitset>

typedef std::bitset<3> moveset;
//itt röviden structok és osztályok fognak szerepelni, amik a gui-n látható
//objektumokhoz fognak kapcsolódni
//pl varázsló, varázslat

//és majd csinálok neki egy cpp fájlt késõbb


//lehet, hogy ezt fogom tovább küldeni a networkingnek egy vektorban
struct Data
{
	std::vector<sf::Vector2f> Positions;
	int Id;
};


/**
* Entity fõosztály
* Ezt folyamatosan frissítgetnem kell majd a GUI-hoz
* Valószínûleg az update loopba teszem
*
* Jó, legyen benne egy pointer ami egy drawable dologra mutat, és onnan frissítgeti
*/
class Entity
{
public:

	Entity() { Id = 0; } //ezt majd kiveszem
	Entity(int id) { Id = id;}
	virtual ~Entity() {}

	Drawable* GetSprite() { return entity; }
	void SetSprite(Drawable* sprite) { entity = sprite; }
	virtual void Update() {
		forces.push_back(sf::Vector2f(0, 0));
		positions.push_back(moveset(0x00));
		Reset();
	}
	virtual void EmptyMovent() { positions.clear(); forces.clear(); }
	std::vector<sf::Vector2f> GetForces() { return forces; }
	std::vector<moveset> GetMoveset() { return positions; }

	void SetInput(bool left, bool right, bool up) { this->left = left; this->right = right; this->up = up; }

	int GetId() { return Id; }

protected:
	Drawable* entity;
	std::vector<sf::Vector2f> forces; //ha van rajta valamilyen erõhatás
	std::vector<moveset> positions; //ha irányítva van

	int Id;
	bool left, right, up;
	void Reset() { left = false; right = false; up = false; }
};

/**
* Minden ami mozog
*/
/*class MovingEntity : public Entity
{
public:
	MovingEntity():Entity() {}
	virtual ~MovingEntity() {}

	sf::Vector2f GetSpeed() { return Speed; }
	sf::Vector2f GetAcceleration() { return Acceleration; }

	void SetSpeed(sf::Vector2f speed) { Speed = speed; }
	void SetAcceleration(sf::Vector2f acc) { Acceleration = acc; }

	void AjdustSpeed(sf::Vector2f speed) { Speed += speed; }
	void AdjustAcceleration(sf::Vector2f acc) { Acceleration += acc; }

	virtual void Update() {
		//positions.push_back(sf::Vector2f(entity->get_x(), entity->get_y()));
	}

protected:
	sf::Vector2f Speed;
	sf::Vector2f Acceleration;
};*/