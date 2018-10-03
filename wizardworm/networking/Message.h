#pragma once

#include <SFML/Network.hpp>

class Message
{
public:
	virtual void execute() = 0;
protected:
	sf::Packet packet;
private:
};