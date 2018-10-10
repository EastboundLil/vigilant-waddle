#pragma once
#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include <vector>
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
	Entity() { Id = IdGenerator++; }
	Entity(int id) { Id = id; IdGenerator++; }
	virtual ~Entity() {}

	Drawable* GetSprite() { return entity; }
	void SetSprite(Drawable* sprite) { entity = sprite; }
	virtual void Update() {}
	virtual void EmptyMovent() { positions.clear(); }
	std::vector<sf::Vector2f> GetMovement() { return positions; }
	int GetId() { return Id; }

protected:
	Drawable* entity;
	std::vector<sf::Vector2f> positions; //ez lesz majd a moveset

	static unsigned int IdGenerator;
	int Id;

	bool Selected;
};

/**
* Minden ami mozog
*/
class MovingEntity : public Entity
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

	//TODO:
	//erre lehet, hogy rá kéne tenni valami idõzítõt, hogy ne fusson le minden frame-re
	virtual void Update() {
		Speed += Acceleration;
		entity->set_pos(entity->get_x() + Speed.x, entity->get_y() + Speed.y);
		positions.push_back(sf::Vector2f(entity->get_x(), entity->get_y()));
	}

protected:
	sf::Vector2f Speed;
	sf::Vector2f Acceleration;
};