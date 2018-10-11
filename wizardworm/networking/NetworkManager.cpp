#include "stdafx.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager() :
	connectionHandler(nullptr),
	connectionThread(&NetworkManager::startThread,this)
{

}


NetworkManager::~NetworkManager()
{

}

void NetworkManager::setGUIInterface(std::shared_ptr<IWindow> IGuiManager)
{
	guiManager = IGuiManager;
}

void NetworkManager::startAsServer()
{
	if (connectionHandler == nullptr)
	{
		connectionHandler = std::make_shared<LanServerHandler>(this);
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
		connectionHandler = std::make_shared<LanClientHandler>(this);
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

void NetworkManager::onMessageReceived(sf::Packet packet)
{
	Message* message = messageHandler.parsePacket(packet);

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