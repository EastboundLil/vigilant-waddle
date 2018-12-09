#include "stdafx.h"
#include "ClientEngine.h"


ClientEngine::ClientEngine() : IEngine()
{
}


ClientEngine::~ClientEngine()
{
}

std::vector<Data> ClientEngine::GenerateMoveset()
{
	std::vector<Data> movesets;
	for (int i = 0; i < entities.size(); i++)
	{
		/*Data d;
		d.Id = entities[i].GetId();
		d.Positions = entities[i].GetMovement();
		entities[i].EmptyMovent();
		movesets.push_back(d);*/
	}

	return movesets;
}

void ClientEngine::Update()
{
	bool up, left, right;
	//get values from gui
	currentPlayer->AddKeyboardData(up, left, right);
}
