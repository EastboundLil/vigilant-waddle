#include "stdafx.h"
#include "LanClientHandler.h"


LanClientHandler::LanClientHandler()
{
}


LanClientHandler::~LanClientHandler()
{
}

void LanClientHandler::start()
{
	LOG("Connecting to " << ipAddress.toString << "...");
	connectionStatus = socket.connect(ipAddress, PORT);

	if (connectionStatus != sf::Socket::Done)
	{
		LOG("Connection error!");
	}
}

void LanClientHandler::sendData()
{
	char data[100] = "Hello!";

	if (socket.send(data, 100) != sf::Socket::Done)
	{
		LOG("Error sending data!");
	}
}

