#include "stdafx.h"
#include "NetworkManager.h"


NetworkManager::NetworkManager() :
	handler(nullptr)
{

}


NetworkManager::~NetworkManager()
{

}


void NetworkManager::startAsServer()
{
	if (handler == nullptr)
	{
		handler = std::make_unique<LanServerHandler>();
	}
	else
	{
		LOG("Handler is not null, skipping...");
	}
}

void NetworkManager::startAsClient()
{
	if (handler == nullptr)
	{
		handler = std::make_unique<LanClientHandler>();
	}
	else
	{
		LOG("Handler is not null, skipping...");
	}
}

void NetworkManager::startConnection()
{
	if (handler != nullptr)
	{
		handler->start();
	}
	else
	{
		LOG("Handler is nullptr!");
	}
}

void NetworkManager::setRemoteAddress(std::string ipAddress)
{
	if (handler != nullptr)
	{
		handler->setAddress(ipAddress);
	}
	else
	{
		LOG("Handler is nullptr!");
	}
}