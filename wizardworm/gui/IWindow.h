#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

#include "networking/INWManager.h"

class IWindow
{
public:

	virtual void eventhandler() = 0;

	virtual void onTimerEndMsg() = 0;
};