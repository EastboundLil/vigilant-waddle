#pragma once
#include "LanHandler.h"


class LanServerHandler :
	public LanHandler
{
public:
	LanServerHandler();
	~LanServerHandler();

private:
	sf::TcpListener listener;
};

