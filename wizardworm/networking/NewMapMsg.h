#pragma once

#include "Message.h"

#include <sstream>

class NewMapMsg : public Message
{
public:
	NewMapMsg(std::stringstream& map)
	{
		streamOfMapElements << map.rdbuf();
	}

	void execute() override
	{
		ApplicationManager::getInstance().getGuiManager()->receiveMap(streamOfMapElements);
	}

private:
	std::stringstream streamOfMapElements;
};