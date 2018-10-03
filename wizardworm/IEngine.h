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

	//ez csak a szervern�l lesz megh�vva, ez sz�molja ki a movesetek alapj�n a... mindent
	virtual void CalculateMoveset() = 0;

	//ezt kell futtatni a f� cikluson bel�l.
	//csin�ljam meg ezt oszt�lyon bel�l, vagy valahol k�v�l lesz futtatva?
	virtual void Update();

	Entity* GetEntity(int pos);
	void AddEntity(Entity& entity);

protected:
	//nagyon gondolkozom, hogy a vektorba ne csak pointereket t�roljak.
	//mit gondoltok, legyen �gy:
	std::vector<Entity> entities;
	//vagy �gy?
	//std::vector<Entity*> entities;
	//persze, akkor a destrucktorba mindent t�r�ln�m kell
};

