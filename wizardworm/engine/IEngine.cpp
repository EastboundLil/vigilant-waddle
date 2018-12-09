#include "stdafx.h"
#include "IEngine.h"

#define MOVING_SPEED 5
#define GRAVITY 1
#define FPS 60
#define JUMP_FORCE 10

IEngine::IEngine()
{
	keyboardInput = false;
	fpsTime = (1 / FPS) * 1000;
	timer.restart();
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
			}

			if (current_entity->GetJumpSpeed() != 0)
			{
				current_entity->AdjustPosition(0, current_entity->GetJumpSpeed());
			}

			keyboardInput = false;
		}

		timer.restart();
	}
}

void IEngine::Move(bool up, bool left, bool right)
{
	if (!keyboardInput)
	{
		keyboardInput = true;
		data.Up = up;
		data.Left = left;
		data.Right = right;
	}
}

void IEngine::AddPlayer(std::vector<Drawable*> entities)
{
	PlayerData* pd = new PlayerData(entities);
	players.push_back(pd);
}
