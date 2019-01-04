#pragma once
#include "Objects.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Wizard.h"

class IEngine
{
public:
	IEngine();
	virtual ~IEngine();

	//ezt kell futtatni a fõ cikluson belül.
	//csináljam meg ezt osztályon belül, vagy valahol kívül lesz futtatva?
	virtual void Update();

	virtual void Move(bool up, bool left, bool right);

	virtual void AddPlayer(std::vector<Wizard*> entities);
	virtual void Switch();

	//network foka moka
	virtual void SendData();
	virtual void ReceiveData();
	
	void switchplayerBence();
	void Start();

	virtual sf::Vector2f Find(Drawable* item);

protected:
	sf::Mutex mut1;
	sf::Mutex mut2;

	std::vector<PlayerData*> players;
	std::vector<sf::IntRect> blockRect;
	int currentPlayer;
	bool keyboardInput;
	KeyboardData data;
	float fpsTime;

	sf::Clock timer;
	sf::Clock roundTimer;

	sf::Thread thread;

	int currentEngineState;
	int engineType;

	void StartThread();
	void ColCheck(sf::Vector2f direction, bool gravCheck = true);
	void GravCheck();
	void ReloadCollision();

	enum EngineState
	{
		Working = 0,
		Sending = 1,
		Receiveing = 2,
		Calculating = 3,
		Playing = 4,
		Waiting = 5
	};

	enum EngineType
	{
		Server = 0,
		Client = 1,
		Undefined = 2
	};

	bool reloaded;
	unsigned int cycleCounter;
};

