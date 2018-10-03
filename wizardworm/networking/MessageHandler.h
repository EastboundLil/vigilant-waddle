#pragma once

#include <SFML/Network.hpp>

#include "Logger.h"
#include "Message.h"
#include "MoveSetMsg.h"
#include "TimerEndMsg.h"

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();

	Message* parsePacket(sf::Packet packet);
	sf::Packet createMoveSetMsg(std::vector<std::string> moveSet);
	sf::Packet createTimerEndMsg();

private:

};

