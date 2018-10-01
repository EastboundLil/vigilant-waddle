#pragma once
#include <SFML/Graphics.hpp>
//itt röviden structok és osztályok fognak szerepelni, amik a gui-n látható
//objektumokhoz fognak kapcsolódni
//pl varázsló, varázslat


/**
* Entity fõosztály
* Ezt folyamatosan frissítgetnem kell majd a GUI-hoz
* Valószínûleg az update loopba teszem
*/
class Entity
{
public:
	Entity() {}
	virtual ~Entity() {}

	sf::Sprite GetSprite() { return entity; }
	void SetSprite(sf::Sprite sprite) { entity = sprite; }
	virtual void Update() {}

protected:
	sf::Sprite entity;
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
	//TODO:
	//erre lehet, hogy rá kéne tenni valami idõzítõt, hogy ne fusson le minden frame-re
	virtual void Update() { Speed += Acceleration; entity.setPosition(entity.getPosition() + Speed); }

protected:
	sf::Vector2f Speed;
	sf::Vector2f Acceleration;
};