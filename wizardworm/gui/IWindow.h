#pragma once

class IWindow
{
public:
	virtual void thegame() = 0;
	virtual void startMenu() = 0;
	virtual void mapSelector() = 0;
	
	virtual void onTimerEndMsg() = 0;
	virtual void receiveMap(std::stringstream& map) = 0;
};