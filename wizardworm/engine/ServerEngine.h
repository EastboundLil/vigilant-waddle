#pragma once
#include "IEngine.h"
#include <map>

class ServerEngine :
	public IEngine
{
public:
	ServerEngine(int playerNum);
	~ServerEngine();

private:
	std::map<int, bool> PlayerReady;
};

