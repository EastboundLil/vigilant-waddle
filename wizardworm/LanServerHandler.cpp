#include "stdafx.h"
#include "LanServerHandler.h"


LanServerHandler::LanServerHandler()
{
}


LanServerHandler::~LanServerHandler()
{
}

void LanServerHandler::start()
{
	LOG("Starting listening...");

	connectionStatus = listener.listen(PORT);

	if (connectionStatus != sf::Socket::Done)
	{
		LOG("Error starting listener socket!");
	}

	listener.accept(socket);

	if (connectionStatus != sf::Socket::Done)
	{
		LOG("Error accepting connection!");
	}

}

void LanServerHandler::sendData()
{
	char data[100] = "Hello!";

	if (socket.send(data, 100) != sf::Socket::Done)
	{
		LOG("Error sending data!");
	}
}