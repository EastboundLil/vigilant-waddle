#pragma once

#include "Message.h"

class MoveSetMsg : public Message
{
public:
	MoveSetMsg(std::vector<std::string> moves) : moves(moves) {}

	void execute() override
	{
		ApplicationManager::getInstance().getEngineManager()->ReceiveData(moves);
	}

private:
	std::vector<std::string> moves;
};