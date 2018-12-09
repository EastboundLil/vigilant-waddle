#pragma once

class IWindow
{
public:
	virtual void eventhandler() = 0;
	virtual void onTimerEndMsg() = 0;
};