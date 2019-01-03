#include "stdafx.h"
#include "IEngine.h"
#include "ApplicationManager.h"
#include "Window.h"
#include "IWindow.h"

#define MOVING_SPEED 5
#define GRAVITY 0.00000007//0.00000007
#define FPS 60
#define JUMP_FORCE 0.003
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

	reloaded = false;
}


IEngine::~IEngine()
{
}

void IEngine::Update()
{	
	if (players.empty()) return;

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
				ColCheck(sf::Vector2f(1, 0));
			}
			else if (!data.Left && data.Right)
			{
				current_entity->AdjustPosition(sf::Vector2f(1, 0));
				ColCheck(sf::Vector2f(-1, 0));
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
			ColCheck(sf::Vector2f(0, -1));

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
	if (!reloaded)
	{
		ReloadCollision();
		reloaded = true;
	}
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

void IEngine::ColCheck(sf::Vector2f direction)
{
	if (Wizard* w = dynamic_cast<Wizard*>(players[currentPlayer]->GetCurrentEntity()->GetDrawable()))
	{
		Entity* currentEnt = players[currentPlayer]->GetCurrentEntity();
		sf::IntRect wizRec(w->get_x(), w->get_y(), 50, 50);
		Window* win = (Window*)(ApplicationManager::getInstance().getGuiManager().get());

		for (int i = 0; i < blockRect.size(); i++)
		{
			if (!blockRect[i].intersects(wizRec))
				continue;
			if (w->wizard_in_block(win->get_map()->get_all_blocks()[i]))
			{
				currentEnt->AdjustPosition(direction);
				currentEnt->SetJumping(false);
			}
		}
	}
}

void IEngine::ReloadCollision()
{
	Window* win = (Window*)(ApplicationManager::getInstance().getGuiManager().get());
	for (std::shared_ptr<Block> b : win->get_map()->get_all_blocks())
	{
		sf::IntRect rec(b->get_x(), b->get_y(), 50, 50);
		blockRect.push_back(rec);
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
