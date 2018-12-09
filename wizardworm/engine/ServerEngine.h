#pragma once
#include "IEngine.h"
#include <map>

class ServerEngine :
	public IEngine
{
public:
	ServerEngine(int playerNum = 0);
	~ServerEngine();

private:
	std::map<int, bool> PlayerReady;
};

