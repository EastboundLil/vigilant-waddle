#include "stdafx.h"
#include "LanHandler.h"


LanHandler::LanHandler(INWManager* NWManager) :
	networkManager(NWManager),
	ipAddress("127.0.0.1")
{
}


LanHandler::~LanHandler()
{
}

void LanHandler::setAddress(std::string address)
{
	ipAddress = sf::IpAddress(address);
}

std::string LanHandler::getAddress()
{
	return ipAddress.toString();
}