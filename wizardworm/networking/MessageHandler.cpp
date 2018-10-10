#include "MessageHandler.h"

#include "MessageTypes.h"

MessageHandler::MessageHandler()
{
}


MessageHandler::~MessageHandler()
{
}

Message* MessageHandler::parsePacket(sf::Packet packet)
{
	if (packet.getDataSize() == 0)
	{
		LOG("Error: packet to parse is empty!");
		return nullptr;
	}

	//extract header
	int type;
	packet >> type;
	
	switch (type) {
		case MOVE_SET_MSG:
			return onMoveSetMsgReceived(packet);
			break;
		case TIMER_END_MSG:
			return onTimerEndMsgReceived(packet);
			break;
		default:
			LOG("Error: invalid packet header: " << type);
			break;
	}


	return nullptr;
}

sf::Packet MessageHandler::createMoveSetMsg(std::vector<std::string> moveSet)
{
	sf::Packet message;

	//add header
	message << MOVE_SET_MSG;

	//fill body
	for (std::string s : moveSet)
	{
		message << s;
	}

	return message;
}

sf::Packet MessageHandler::createTimerEndMsg()
{
	sf::Packet message;

	//add header
	message << TIMER_END_MSG;

	return message;
}

Message* MessageHandler::onMoveSetMsgReceived(sf::Packet& packet)
{
	std::vector<std::string> moves;

	while (!packet.endOfPacket())
	{
		std::string s;
		packet >> s;
		moves.push_back(s);
	}

	return new MoveSetMsg(moves);
}

Message* MessageHandler::onTimerEndMsgReceived(sf::Packet& packet)
{
	return new TimerEndMsg();
}