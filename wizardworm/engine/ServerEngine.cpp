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
