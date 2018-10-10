#pragma once

#include "Message.h"

class MoveSetMsg : public Message
{
public:
	MoveSetMsg(std::vector<std::string> moves) : moves(moves) {}

	void execute() override
	{

	}

private:
	std::vector<std::string> moves;
};