#pragma once
#include "Objects.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "ApplicationManager.h"
class IEngine
{
public:
	IEngine();
	virtual ~IEngine();

	//még ki kell találni, hogy milyen formában küldjék a movesetet
	virtual std::vector<Data> GenerateMoveset() = 0;

	//itt bejön a moveset az adott playertõl
	virtual void SetMoveset(int player, std::vector<Data>& dataset) = 0;

	//ezt kell futtatni a fõ cikluson belül.
	//csináljam meg ezt osztályon belül, vagy valahol kívül lesz futtatva?
	virtual void Update();

	virtual void Move(bool up, bool left, bool right);

	virtual void AddPlayer(std::vector<Drawable*> entities);

protected:
	std::vector<PlayerData*> players;
	int currentPlayer;
	bool keyboardInput;
	KeyboardData data;
	float fpsTime;

	sf::Clock timer;
	sf::Clock roundTimer;

	int currentEngineState;

	enum EngineState
	{
		Working = 0,
		Sending = 1,
		Receiveing = 2,
		Calculating = 3,
		Playing = 4,
		Waiting = 5
	};
};

