#include "stdafx.h"
#include "IEngine.h"
#include "ApplicationManager.h"

#define MOVING_SPEED 5
#define GRAVITY 0.0000007
#define FPS 60
#define JUMP_FORCE 0.01
#define UP_STEP 10

IEngine::IEngine() : thread(&IEngine::StartThread, this)
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
	if (timer.getElapsedTime().asMilliseconds() >= fpsTime)
	{
		if (keyboardInput)
		{
			mut2.lock();
			Entity* current_entity = players[currentPlayer]->GetCurrentEntity();
			players[currentPlayer]->AddKeyboardData(data.Up, data.Left, data.Right);
			if (data.Up && current_entity->GetJumpSpeed() == 0)
			{
				current_entity->SetJumpSpeed(JUMP_FORCE);
			}
			if (data.Left && !data.Right)
			{
				current_entity->AdjustPosition(sf::Vector2f(-1, 0));
				
			}
			else if (!data.Left && data.Right)
			{
				current_entity->AdjustPosition(sf::Vector2f(1, 0));
				//check in ground
			}

			data.Up = false;
			data.Left = false;
			data.Right = false;
			keyboardInput = false;

			mut2.unlock();
		}

		if (players[currentPlayer]->GetCurrentEntity()->GetJumping())
		{
			players[currentPlayer]->GetCurrentEntity()->AdjustPosition(0, -players[currentPlayer]->GetCurrentEntity()->GetJumpSpeed());
			players[currentPlayer]->GetCurrentEntity()->AdjustJumpSpeed(-(GRAVITY / 2));
			//check in ground

			if (players[currentPlayer]->GetCurrentEntity()->GetYPosition() > 650)
				players[currentPlayer]->GetCurrentEntity()->SetJumping(false);
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
	mut1.lock();
	if (up)
		data.Up = true;
	if (left)
		data.Left = true;
	if (right)
		data.Right = true;
	keyboardInput = up || left || right;
	mut1.unlock();
}

void IEngine::AddPlayer(std::vector<Wizard*> entities)
{
	std::vector<Drawable*> items;
	for (Wizard* w : entities)
		items.push_back(w);
	PlayerData* pd = new PlayerData(items);
	players.push_back(pd);
}

void IEngine::Switch()
{
	players[currentPlayer]->NextEntity();
}

void IEngine::SendData()
{
}

void IEngine::ReceiveData()
{
}

void IEngine::Start()
{
	thread.launch();
}

void IEngine::StartThread()
{
	while (true)
	{
		Update();
	}
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
