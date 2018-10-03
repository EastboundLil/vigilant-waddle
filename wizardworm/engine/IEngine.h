#pragma once
#include "Objects.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class IEngine
{
public:
	IEngine();
	virtual ~IEngine();

	//még ki kell találni, hogy milyen formában küldjék a movesetet
	virtual std::vector<Data> GenerateMoveset() = 0;

	//itt bejön a moveset az adott playertõl
	virtual void SetMoveset(int player, std::vector<Data>& dataset) = 0;

	//ez csak a szervernél lesz meghívva, ez számolja ki a movesetek alapján a... mindent
	virtual void CalculateMoveset() = 0;

	//ezt kell futtatni a fõ cikluson belül.
	//csináljam meg ezt osztályon belül, vagy valahol kívül lesz futtatva?
	virtual void Update();

	Entity* GetEntity(int pos);
	void AddEntity(Entity& entity);

protected:
	//nagyon gondolkozom, hogy a vektorba ne csak pointereket tároljak.
	//mit gondoltok, legyen így:
	std::vector<Entity> entities;
	//vagy így?
	//std::vector<Entity*> entities;
	//persze, akkor a destrucktorba mindent törölnöm kell
};

