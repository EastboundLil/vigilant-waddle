#pragma once

#include <SFML/Network.hpp>

#include "INWManager.h"
#include "Logger.h"

class LanHandler
{
public:
	LanHandler(INWManager* NWManager = nullptr);
	virtual ~LanHandler() = 0;
	virtual void start() = 0;
	void setAddress(std::string ipAddress);
	std::string getAddress();
	virtual void sendData(sf::Packet) = 0;
	virtual void receiveData() = 0;
	virtual void onDataReceived(sf::Packet packet) = 0;

protected:
	sf::TcpSocket socket;
	sf::IpAddress ipAddress;
	sf::Socket::Status connectionStatus;

	const short PORT = 9000;

	INWManager* networkManager = nullptr;

private:

};

