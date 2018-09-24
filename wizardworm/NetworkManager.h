#pragma once

#include "LanHandler.h"

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

private:
	LanHandler* handler;
};

