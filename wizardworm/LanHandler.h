#pragma once

#include <SFML/Network.hpp>

class LanHandler
{
public:
	LanHandler();
	virtual ~LanHandler();

private:
	sf::TcpSocket socket;
};

