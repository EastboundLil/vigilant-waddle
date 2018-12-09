#include "stdafx.h"
#include "ServerEngine.h"


ServerEngine::ServerEngine(int playerNum) : IEngine()
{
	for (int i = 0; i < playerNum; i++)
		PlayerReady.insert(std::make_pair(i, false));
}


ServerEngine::~ServerEngine()
{
}

std::vector<Data> ServerEngine::GenerateMoveset()
{
	std::vector<Data> movesets;
	for (int i = 0; i < entities.size(); i++)
	{
		Data d;
		d.Id = entities[i].GetId();
		//d.Positions = entities[i].GetMovement();
		entities[i].EmptyMovent();
		movesets.push_back(d);
	}

	return movesets;
}

void ServerEngine::SetMoveset(int player, std::vector<Data>& dataset)
{
	PlayerReady[player] = true;
}

void ServerEngine::Update()
{
}
