#include "stdafx.h"
#include "Window.h"
#include "NetworkManager.h"

int main()
{
	NetworkManager* nwManager = new NetworkManager();

	Window * window = new Window(nwManager);
	window->eventhandler();
	
	return 0;
}