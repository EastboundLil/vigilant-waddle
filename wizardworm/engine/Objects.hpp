#pragma once
#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include <vector>
//itt r�viden structok �s oszt�lyok fognak szerepelni, amik a gui-n l�that�
//objektumokhoz fognak kapcsol�dni
//pl var�zsl�, var�zslat

//�s majd csin�lok neki egy cpp f�jlt k�s�bb


//lehet, hogy ezt fogom tov�bb k�ldeni a networkingnek egy vektorban
struct Data
{
	std::vector<sf::Vector2f> Positions;
	int Id;
};


/**
* Entity f�oszt�ly
* Ezt folyamatosan friss�tgetnem kell majd a GUI-hoz
* Val�sz�n�leg az update loopba teszem
*
* J�, legyen benne egy pointer ami egy drawable dologra mutat, �s onnan friss�tgeti
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
	//erre lehet, hogy r� k�ne tenni valami id�z�t�t, hogy ne fusson le minden frame-re
	virtual void Update() {
		Speed += Acceleration;
		entity->set_pos(entity->get_x() + Speed.x, entity->get_y() + Speed.y);
		positions.push_back(sf::Vector2f(entity->get_x(), entity->get_y()));
	}

protected:
	sf::Vector2f Speed;
	sf::Vector2f Acceleration;
};