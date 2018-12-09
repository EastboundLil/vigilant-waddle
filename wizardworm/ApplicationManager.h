#pragma once

#include "gui/IWindow.h"
#include "networking/INWManager.h"
#include "engine/IEngine.h"

class IWindow;
class INWManager;
class IEngine;

class ApplicationManager
{
public:
	static ApplicationManager& getInstance()
	{
		static ApplicationManager instance;
		return instance;
	}

	ApplicationManager(ApplicationManager const&) = delete;
	void operator=(ApplicationManager const&) = delete;

	void setGuiManager(std::shared_ptr<IWindow> gui)				{ guiManager = gui; }
	void setNetworkManager(std::shared_ptr<INWManager> networking)	{ networkManager = networking; }
	void setEngineManager(std::shared_ptr<IEngine> engine)			{ engineManager = engine; }
	
	std::shared_ptr<IWindow>	getGuiManager()		{ return guiManager; }
	std::shared_ptr<INWManager> getNetworkManager() { return networkManager; }
	std::shared_ptr<IEngine>	getEngineManager()	{ return engineManager;  }

private:
	ApplicationManager() : guiManager(nullptr), networkManager(nullptr), engineManager(nullptr) {};

	std::shared_ptr<IWindow>	guiManager;
	std::shared_ptr<INWManager> networkManager;
	std::shared_ptr<IEngine>	engineManager;
};