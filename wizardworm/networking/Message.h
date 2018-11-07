#pragma once

#include <SFML/Network.hpp>

#include "ApplicationManager.h"

class Message
{
public:
	virtual void execute() = 0;
private:
};