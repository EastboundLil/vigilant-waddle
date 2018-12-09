#pragma once

class IWindow
{
public:
	virtual void eventhandler() = 0;
	virtual void onTimerEndMsg() = 0;

	virtual void setNetworkManager(std::shared_ptr<INWManager> networking) = 0;
	virtual void setEngineManager(std::shared_ptr<IEngine> engine) = 0;
};