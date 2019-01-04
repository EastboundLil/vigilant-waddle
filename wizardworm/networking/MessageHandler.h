#pragma once
#include <SFML/Network.hpp>
#include <sstream>

#include "Logger.h"
#include "Message.h"
#include "MoveSetMsg.h"
#include "TimerEndMsg.h"
#include "NewMapMsg.h"

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();

	Message* parsePacket(sf::Packet packet);
	sf::Packet createMoveSetMsg(std::vector<std::string> moveSet);
	sf::Packet createTimerEndMsg();
	sf::Packet createNewMapMsg(std::stringstream& map);

private:
	Message* onMoveSetMsgReceived(sf::Packet& packet);
	Message* onTimerEndMsgReceived(sf::Packet& packet);
	Message* onNewMapMsgReceived(sf::Packet& packet);
};

