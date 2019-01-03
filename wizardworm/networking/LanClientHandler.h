#pragma once
#include "LanHandler.h"
class LanClientHandler :
	public LanHandler
{
public:
	LanClientHandler();
	~LanClientHandler();

	void start() override;
	void sendData(sf::Packet packet) override;
	void receiveData() override;
	void onDataReceived(sf::Packet packet) override;
};