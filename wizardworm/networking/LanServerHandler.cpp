#include "stdafx.h"
#include "LanServerHandler.h"

#include "ApplicationManager.h"

LanServerHandler::LanServerHandler()
{
}


LanServerHandler::~LanServerHandler()
{
}

void LanServerHandler::start()
{
	while (true)
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
		else
		{
			LOG("Connection accepted!");
		}

		receiveData();
	}

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
		sf::Socket::Status receiveStatus = socket.receive(packet);
		if (receiveStatus == sf::Socket::Done)
		{
			onDataReceived(packet);
		}
		else if (receiveStatus == sf::Socket::Disconnected)
		{
			LOG("Socket has been disconnected!");
			return;
		}
		else
		{
			LOG("Error receiving data!");
		}
	}
}

void LanServerHandler::onDataReceived(sf::Packet packet)
{
	ApplicationManager::getInstance().getNetworkManager()->onMessageReceived(packet);
}