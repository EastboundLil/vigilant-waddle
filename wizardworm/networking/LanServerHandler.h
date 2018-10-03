#pragma once
#include "LanHandler.h"


class LanServerHandler :
	public LanHandler
{
public:
	LanServerHandler(INWManager* NWManager = nullptr);
	~LanServerHandler();

	void start() override;
	void sendData(sf::Packet packet) override;
	void receiveData() override;
	void onDataReceived(sf::Packet packet) override;

private:
	sf::TcpListener listener;
};

