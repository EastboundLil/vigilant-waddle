#pragma once

#include <SFML/Network.hpp>

#include "Logger.h"

class LanHandler
{
public:
	LanHandler();
	virtual ~LanHandler() = 0;
	virtual void start() = 0;
	void setAddress(std::string ipAddress);
	std::string getAddress();
	virtual void sendData() = 0;

protected:
	sf::TcpSocket socket;
	sf::IpAddress ipAddress;
	sf::Socket::Status connectionStatus;

	const short PORT = 9000;

private:

};

