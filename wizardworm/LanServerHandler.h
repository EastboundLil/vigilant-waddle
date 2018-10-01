#pragma once
#include "LanHandler.h"


class LanServerHandler :
	public LanHandler
{
public:
	LanServerHandler();
	~LanServerHandler();

	void start() override;
	void sendData() override;

private:
	sf::TcpListener listener;
};

