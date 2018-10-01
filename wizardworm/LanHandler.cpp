#include "stdafx.h"
#include "LanHandler.h"


LanHandler::LanHandler()
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