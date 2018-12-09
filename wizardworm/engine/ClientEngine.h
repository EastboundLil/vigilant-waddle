#pragma once
#include "IEngine.h"
class ClientEngine :
	public IEngine
{
public:
	ClientEngine();
	~ClientEngine();

	void Update();
private:
	PlayerData* currentPlayer;
};

