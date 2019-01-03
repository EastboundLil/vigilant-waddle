#include "stdafx.h"
#include "Window.h"
#include "NetworkManager.h"
#include "ServerEngine.h"

#include "ApplicationManager.h"

int main()
{
	ApplicationManager::getInstance().setNetworkManager(std::make_shared<NetworkManager>());
	ApplicationManager::getInstance().setGuiManager(std::make_shared<Window>());
	ApplicationManager::getInstance().setEngineManager(std::make_shared<ServerEngine>());

	ApplicationManager::getInstance().init();

	ApplicationManager::getInstance().getGuiManager()->startMenu();
	
	return 0;
}