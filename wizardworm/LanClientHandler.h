#pragma once
#include "LanHandler.h"
class LanClientHandler :
	public LanHandler
{
public:
	LanClientHandler();
	~LanClientHandler();

	void start() override;
	void sendData() override;
	void onDataReceived(char data[100]) override;
};

