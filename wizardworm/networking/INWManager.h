#pragma once

#include <string>
#include <SFML/Network.hpp>

class INWManager
{
public:

	virtual void startAsServer() = 0;
	virtual void startAsClient() = 0;
	virtual void startConnection() = 0;
	virtual void stopNetworking() = 0;

	virtual sf::Socket::Status getNetworkStatus() = 0;

	virtual std::string getOwnAddress() = 0;
	virtual void setRemoteAddress(std::string ipAddress) = 0;
	virtual bool isRunningAsHost() = 0;

	virtual void onMessageReceived(sf::Packet packet) = 0;

	virtual void sendMoveSetMsg(std::vector<std::string> moveSet) = 0;
	virtual void sendTimerEndMsg() = 0;
	virtual void sendNewMapMsg(std::stringstream& map) = 0;
};