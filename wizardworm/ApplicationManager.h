#pragma once

#include "gui/IWindow.h"
#include "networking/INWManager.h"

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
	
	std::shared_ptr<IWindow>	getGuiManager()		{ return guiManager; }
	std::shared_ptr<INWManager> getNetworkManager() { return networkManager; }

private:
	ApplicationManager() : guiManager(nullptr), networkManager(nullptr) {};

	std::shared_ptr<IWindow>	guiManager;
	std::shared_ptr<INWManager> networkManager;
};