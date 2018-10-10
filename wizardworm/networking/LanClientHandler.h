#pragma once
#include "LanHandler.h"
class LanClientHandler :
	public LanHandler
{
public:
	LanClientHandler(INWManager* NWManager = nullptr);
	~LanClientHandler();

	void start() override;
	void sendData(sf::Packet packet) override;
	void receiveData() override;
	void onDataReceived(sf::Packet packet) override;
};

