#pragma once

#include "LanHandler.h"
#include "LanClientHandler.h"
#include "LanServerHandler.h"
#include "Logger.h"



class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void startAsServer();
	void startAsClient();
	void startConnection();

	void setRemoteAddress(std::string ipAddress);


private:
	std::unique_ptr<LanHandler> handler;
};

