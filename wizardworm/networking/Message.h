#pragma once

#include <SFML/Network.hpp>

#include "gui/IWindow.h"

class Message
{
public:
	virtual void execute() = 0;
	void setGuiManager(IWindow* IGUIManager) { guiManager = IGUIManager; }
protected:
	IWindow* guiManager;
	sf::Packet packet;
private:
};