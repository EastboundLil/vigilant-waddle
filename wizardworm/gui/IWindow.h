#pragma once

class IWindow
{
public:
	virtual void eventhandler() = 0;
	virtual void onTimerEndMsg() = 0;
	virtual void startMenu() = 0;
	virtual void mapSelector() = 0;
};