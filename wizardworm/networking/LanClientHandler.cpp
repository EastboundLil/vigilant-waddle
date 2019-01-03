#include "stdafx.h"
#include "LanClientHandler.h"

#include "ApplicationManager.h"

LanClientHandler::LanClientHandler()
{
}


LanClientHandler::~LanClientHandler()
{
	socket.disconnect();
}

void LanClientHandler::start()
{
	LOG("Connecting to " << ipAddress.toString() << "...");
	connectionStatus = socket.connect(ipAddress, PORT);

	if (connectionStatus != sf::Socket::Done)
	{
		LOG("Connection error: " << connectionStatus);
	}
	else
	{
		LOG("Connected!");
	}
}


void LanClientHandler::sendData(sf::Packet packet)
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

void LanClientHandler::receiveData()
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

void LanClientHandler::onDataReceived(sf::Packet packet)
{
	ApplicationManager::getInstance().getNetworkManager()->onMessageReceived(packet);
}

