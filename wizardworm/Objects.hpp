#pragma once
#include <SFML/Graphics.hpp>
//itt r�viden structok �s oszt�lyok fognak szerepelni, amik a gui-n l�that�
//objektumokhoz fognak kapcsol�dni
//pl var�zsl�, var�zslat


/**
* Entity f�oszt�ly
* Ezt folyamatosan friss�tgetnem kell majd a GUI-hoz
* Val�sz�n�leg az update loopba teszem
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
	//erre lehet, hogy r� k�ne tenni valami id�z�t�t, hogy ne fusson le minden frame-re
	virtual void Update() { Speed += Acceleration; entity.setPosition(entity.getPosition() + Speed); }

protected:
	sf::Vector2f Speed;
	sf::Vector2f Acceleration;
};