#pragma once

#include "INWManager.h"

#include "LanHandler.h"
#include "LanClientHandler.h"
#include "LanServerHandler.h"
#include "MessageHandler.h"
#include "Logger.h"


class NetworkManager : public INWManager
{
public:
	NetworkManager();
	~NetworkManager();

	void startAsServer() override;
	void startAsClient() override;
	void startConnection() override;

	void setRemoteAddress(std::string ipAddress) override;

	void onMessageReceived(sf::Packet packet) override;

	void sendMoveSetMsg(std::vector<std::string> moveSet) override;
	void sendTimerEndMsg() override;


private:
	std::unique_ptr<LanHandler> connectionHandler;
	MessageHandler messageHandler;
};
