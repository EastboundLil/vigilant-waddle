#include "stdafx.h"
#include "LanClientHandler.h"


LanClientHandler::LanClientHandler(INWManager* NWManager) :
	LanHandler(NWManager)
{
}


LanClientHandler::~LanClientHandler()
{
}

void LanClientHandler::start()
{
	LOG("Connecting to " << ipAddress.toString() << "...");
	connectionStatus = socket.connect(ipAddress, PORT);

	if (connectionStatus != sf::Socket::Done)
	{
		LOG("Connection error!");
	}
	else
	{
		LOG("Connected!");
	}
}

void LanClientHandler::sendData(sf::Packet packet)
{
	char data[100] = "Hello!";

	if (socket.send(data, 100) != sf::Socket::Done)
	{
		LOG("Error sending data!");
	}
}

void LanClientHandler::onDataReceived(sf::Packet packet)
{

}

