#pragma once

#include "Message.h"

class TimerEndMsg : public Message
{
public:
	void execute() override
	{
		LOG("Executing TimerEndMsg!");
		guiManager->onTimerEndMsg();
	}

private:
};
