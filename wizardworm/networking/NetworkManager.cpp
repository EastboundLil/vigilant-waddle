#include "stdafx.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager() :
	connectionHandler(nullptr),
	connectionThread(&NetworkManager::startThread,this)
{

}


NetworkManager::~NetworkManager()
{
	connectionThread.terminate();
}

void NetworkManager::startAsServer()
{
	runningAsHost = true;
	if (connectionHandler == nullptr)
	{
		connectionHandler = std::make_shared<LanServerHandler>();
	}
	else
	{
		LOG("Handler is not null, skipping...");
	}
}

void NetworkManager::startAsClient()
{
	runningAsHost = false;
	if (connectionHandler == nullptr)
	{
		connectionHandler = std::make_shared<LanClientHandler>();
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
		connectionThread.launch();
	}
	else
	{
		LOG("Handler is nullptr!");
	}
}

void NetworkManager::stopNetworking()
{
	connectionHandler = nullptr;
}

sf::Socket::Status NetworkManager::getNetworkStatus()
{
	return connectionHandler->getStatus();
}

std::string NetworkManager::getOwnAddress()
{
	return sf::IpAddress::getLocalAddress().toString();
}

void NetworkManager::startThread()
{
	connectionHandler->start();
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

bool NetworkManager::isRunningAsHost()
{
	return runningAsHost;
}

void NetworkManager::onMessageReceived(sf::Packet packet)
{
	Message* message = messageHandler.parsePacket(packet);
	LOG("message received");
	if (message != nullptr)
	{
		message->execute();
		delete message;
	}
	else LOG("message is nullptr!");

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

void NetworkManager::sendNewMapMsg(std::stringstream& map)
{
	sf::Packet message = messageHandler.createNewMapMsg(map);
	connectionHandler->sendData(message);
}