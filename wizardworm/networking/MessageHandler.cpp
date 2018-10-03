#include "MessageHandler.h"



MessageHandler::MessageHandler()
{
}


MessageHandler::~MessageHandler()
{
}

Message* MessageHandler::parsePacket(sf::Packet packet)
{
	return nullptr;
}

sf::Packet MessageHandler::createMoveSetMsg(std::vector<std::string> moveSet)
{
	return sf::Packet();
}

sf::Packet MessageHandler::createTimerEndMsg()
{
	return sf::Packet();
}