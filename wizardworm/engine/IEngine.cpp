#include "stdafx.h"
#include "IEngine.h"
#include "ApplicationManager.h"

#define MOVING_SPEED 5
#define GRAVITY 1
#define FPS 60
#define JUMP_FORCE 10
#define UP_STEP 10

IEngine::IEngine()
{
	keyboardInput = false;
	fpsTime = (1 / FPS) * 1000;
	timer.restart();
	roundTimer.restart();

	engineType = EngineType::Undefined;
	currentEngineState = EngineState::Waiting;
	currentPlayer = 0;
}


IEngine::~IEngine()
{
}

void IEngine::Update()
{
	if (timer.getElapsedTime().asMilliseconds() >= fpsTime && roundTimer.getElapsedTime().asSeconds() < 30)
	{
		if (keyboardInput)
		{
			Entity* current_entity = players[currentPlayer]->GetCurrentEntity();
			players[currentPlayer]->AddKeyboardData(data.Up, data.Left, data.Right);
			if (data.Up && current_entity->GetJumpSpeed() == 0)
			{
				current_entity->SetJumpSpeed(JUMP_FORCE);
			}
			if (data.Left && !data.Right)
			{
				current_entity->AdjustPosition(-1, 0);
				
			}
			else if (!data.Left && data.Right)
			{
				current_entity->AdjustPosition(1, 0);
				//check in ground
			}

			if (current_entity->GetJumpSpeed() != 0)
			{
				current_entity->AdjustPosition(0, current_entity->GetJumpSpeed());
				current_entity->AdjustJumpSpeed(-GRAVITY);
				//check in ground
			}

			data.Up = false;
			data.Left = false;
			data.Right = false;
			keyboardInput = false;
		}

		timer.restart();
	}
	else if (roundTimer.getElapsedTime().asSeconds() >= 30)
	{
		if (engineType == EngineType::Client)
			SendData();
		else
			ReceiveData();
		//send data to server
		//server calculate response
		//???
		//profit
	}
}

void IEngine::Move(bool up, bool left, bool right)
{
	if (up)
		data.Up = true;
	if (left)
		data.Left = true;
	if (right)
		data.Right = true;
}

void IEngine::AddPlayer(std::vector<Wizard*> entities)
{
	std::vector<Drawable*> items;
	for (Wizard* w : entities)
		items.push_back(w);
	PlayerData* pd = new PlayerData(items);
	players.push_back(pd);
}

void IEngine::SendData()
{
}

void IEngine::ReceiveData()
{
}

sf::Vector2f IEngine::Find(Drawable * item)
{
	for (int i = 0; i < players[currentPlayer]->GetEntityCount(); i++)
	{
		if (players[currentPlayer]->GetEntityWithNum(i)->GetDrawable() == item)
			return players[currentPlayer]->GetEntityWithNum(i)->GetPosition();
	}

	return sf::Vector2f(-1, -1);
}
