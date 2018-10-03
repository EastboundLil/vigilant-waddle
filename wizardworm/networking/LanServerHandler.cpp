#include "stdafx.h"
#include "LanServerHandler.h"


LanServerHandler::LanServerHandler(INWManager* NWManager) :
	LanHandler(NWManager)
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

	connectionStatus = listener.accept(socket);

	if (connectionStatus != sf::Socket::Done)
	{
		LOG("Error accepting connection!");
	}

	char data[100];
	std::size_t received;

	if (socket.receive(data, 100, received) != sf::Socket::Done)
	{
		LOG("Error receiving data!");
	}

}

void LanServerHandler::sendData(sf::Packet packet)
{
	char data[100] = "Hello!";

	if (socket.send(data, 100) != sf::Socket::Done)
	{
		LOG("Error sending data!");
	}
}

void LanServerHandler::onDataReceived(sf::Packet packet)
{
	networkManager->onMessageReceived(packet);
}