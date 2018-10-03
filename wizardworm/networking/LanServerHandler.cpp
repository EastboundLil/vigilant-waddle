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

	receiveData();

}

void LanServerHandler::sendData(sf::Packet packet)
{
	sf::Socket::Status messageStatus = socket.send(packet);

	if (messageStatus == sf::Socket::Done)
	{
		LOG("Message sent");
	}
	else
	{
		LOG("Error sending message: " << messageStatus);
	}
}

void LanServerHandler::receiveData()
{
	while (true)
	{
		sf::Packet packet;
		if (socket.receive(packet) != sf::Socket::Done)
		{
			LOG("Error receiving data!");
		}
		else
		{
			onDataReceived(packet);
		}
	}
}

void LanServerHandler::onDataReceived(sf::Packet packet)
{
	networkManager->onMessageReceived(packet);
}