#include "stdafx.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager() :
	connectionHandler(nullptr)
{

}


NetworkManager::~NetworkManager()
{

}


void NetworkManager::startAsServer()
{
	if (connectionHandler == nullptr)
	{
		connectionHandler = std::make_unique<LanServerHandler>(this);
	}
	else
	{
		LOG("Handler is not null, skipping...");
	}
}

void NetworkManager::startAsClient()
{
	if (connectionHandler == nullptr)
	{
		connectionHandler = std::make_unique<LanClientHandler>(this);
	}
	else
	{
		LOG("Handler is not null, skipping...");
	}
}

void NetworkManager::startConnection()
{
	if (connectionHandler != nullptr)
	{
		connectionHandler->start();
	}
	else
	{
		LOG("Handler is nullptr!");
	}
}

void NetworkManager::setRemoteAddress(std::string ipAddress)
{
	if (connectionHandler != nullptr)
	{
		connectionHandler->setAddress(ipAddress);
	}
	else
	{
		LOG("Handler is nullptr!");
	}
}

void NetworkManager::onMessageReceived(sf::Packet packet)
{
	Message* message = messageHandler.parsePacket(packet);
	message->execute();
	delete message;
}

void NetworkManager::sendMoveSetMsg(std::vector<std::string> moveSet)
{
	sf::Packet message = messageHandler.createMoveSetMsg(moveSet);
	connectionHandler->sendData(message);
}

void NetworkManager::sendTimerEndMsg()
{
	sf::Packet message = messageHandler.createTimerEndMsg();
	connectionHandler->sendData(message);
}