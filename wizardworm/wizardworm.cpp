#include "stdafx.h"
#include "Window.h"
#include "NetworkManager.h"

#include "ApplicationManager.h"

int main()
{
	ApplicationManager::getInstance().setNetworkManager(std::make_shared<NetworkManager>());
	ApplicationManager::getInstance().setGuiManager(std::make_shared<Window>());

	std::shared_ptr<IWindow> window = ApplicationManager::getInstance().getGuiManager();
	window->eventhandler();
	
	return 0;
}