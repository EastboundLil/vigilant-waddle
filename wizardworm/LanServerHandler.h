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
	void onDataReceived(char data[100]) override;

private:
	sf::TcpListener listener;
};

