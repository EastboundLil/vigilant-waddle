#pragma once
#include "Objects.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class IEngine
{
public:
	IEngine();
	virtual ~IEngine();

	//m�g ki kell tal�lni, hogy milyen form�ban k�ldj�k a movesetet
	virtual std::vector<Data> GenerateMoveset() = 0;

	//itt bej�n a moveset az adott playert�l
	virtual void SetMoveset(int player, std::vector<Data>& dataset) = 0;

	//ezt kell futtatni a f� cikluson bel�l.
	//csin�ljam meg ezt oszt�lyon bel�l, vagy valahol k�v�l lesz futtatva?
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
};

