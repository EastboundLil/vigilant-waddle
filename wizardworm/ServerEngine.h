#pragma once
#include "IEngine.h"
#include <map>

class ServerEngine :
	public IEngine
{
public:
	ServerEngine(int playerNum);
	~ServerEngine();

	std::vector<Data> GenerateMoveset();
	void SetMoveset(int player, std::vector<Data>& dataset);

private:
	std::map<int, bool> PlayerReady;

	void CalculateAll();
};

