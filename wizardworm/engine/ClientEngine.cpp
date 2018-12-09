#include "stdafx.h"
#include "ClientEngine.h"


ClientEngine::ClientEngine() : IEngine()
{
	engineType = EngineType::Client;
}


ClientEngine::~ClientEngine()
{
}


void ClientEngine::Update()
{
	bool up, left, right;
	//get values from gui
//	currentPlayer->AddKeyboardData(up, left, right);
}
