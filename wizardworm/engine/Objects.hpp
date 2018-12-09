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
struct KeyboardData
{
	bool Up;
	bool Left;
	bool Right;

	KeyboardData(bool up = false, bool left = false, bool right = false)
	{
		Up = up;
		Left = left;
		Right = right;
	}
};

class PlayerData
{
public:
	PlayerData(std::vector<Drawable*>& drawables) {
		for (Drawable* dw : drawables)
			entities.push_back(new Entity(dw));
	}
	~PlayerData() {}

	void SetUsername(std::string name) { username = name; }
	std::string GetUsername() { return username; }
	void AddKeyboardData(bool up, bool left, bool right) {
		if (keyspressed.size() < 1800) keyspressed.push_back(KeyboardData(up, left, right));
	}

	void EmptyKeyboardData() { keyspressed.empty(); }
	bool GetKeyboardData(int step, bool up, bool left) {
		if (step >= 0 && step < 1800)
		{
			if (up)
				return keyspressed[step].Up;
			else if (left)
				return keyspressed[step].Left;
			else
				return keyspressed[step].Right;
		}
	}

	Entity* GetCurrentEntity() { return entities[currentEntity]; }
	void SetCurrentEntity(int id) { currentEntity = id; }
	int GetEntityCount() { return entities.size(); }
	Entity* GetEntityWithNum(int id) { return entities[id]; }
private:
	std::string username;

	std::vector<Entity*> entities;
	int currentEntity;
	std::vector<KeyboardData> keyspressed; //60 fps * 30 sec = 1800 frame
};

class Entity
{
public:
	Entity(Drawable* item) { drawable = item; }
	~Entity() {}

	sf::Vector2f GetPosition() { return position; }
	float GetXPosition() { return position.x; }
	float GetYPosition() { return position.y; }

	void SetPosition(sf::Vector2f pos) { position = pos; }
	void SetPosition(float x, float y) { position = sf::Vector2f(x, y); }

	void AdjustPosition(sf::Vector2f pos) { position += pos; }
	void AdjustPosition(float x, float y) { position += sf::Vector2f(x, y); }

private:
	Drawable* drawable;
	sf::Vector2f position;
};