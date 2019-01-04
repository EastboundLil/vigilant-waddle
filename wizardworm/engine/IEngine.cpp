#include "stdafx.h"
#include "IEngine.h"
#include "ApplicationManager.h"
#include "Window.h"
#include "IWindow.h"

#include "Logger.h"

#define GRAVITY 0.0000007//0.00000007
#define FPS 60
#define JUMP_FORCE 0.003
#define UP_STEP 10
#define BLOCK_SHIFT 2

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
	cycleCounter = 0;
}


IEngine::~IEngine()
{
}

void IEngine::Update()
{	
	if (players.empty()) return;
	if (timer.getElapsedTime().asMilliseconds() >= fpsTime && reloaded)
	{
		mut2.lock();
		cycleCounter++;
		if (currentPlayer == defaultPlayer)
		{
			if (keyboardInput)
			{
				Entity* current_entity = players[currentPlayer]->GetCurrentEntity();
				players[currentPlayer]->AddKeyboardData(data.Up, data.Left, data.Right);
				if (data.Up && current_entity->GetJumpSpeed() == 0)
				{
					current_entity->SetJumpSpeed(JUMP_FORCE);
					current_entity->AdjustPosition(0, -2);
				}
				if (data.Left && !data.Right)
				{
					current_entity->AdjustPosition(sf::Vector2f(-1, 0));
					ColCheck(sf::Vector2f(2, 0));
					current_entity->AdjustJumpSpeed(-0.001);
					ColCheck(sf::Vector2f(0, 0.002));
				}
				else if (!data.Left && data.Right)
				{
					current_entity->AdjustPosition(sf::Vector2f(1, 0));
					ColCheck(sf::Vector2f(-2, 0));
					current_entity->SetJumpSpeed(-0.001);
					ColCheck(sf::Vector2f(0, 0.002));
				}

				data.Up = false;
				data.Left = false;
				data.Right = false;
				keyboardInput = false;

			}
			else
				players[currentPlayer]->AddKeyboardData(false, false, false);
		}
		else
		{
			if (OtherKeys.size() > 0)
			{
				Entity* current_entity = players[currentPlayer]->GetCurrentEntity();
				if (OtherKeys[0].Up)
				{
					current_entity->SetJumpSpeed(JUMP_FORCE);
					current_entity->AdjustPosition(0, -2);
				}
				if (OtherKeys[0].Left && !OtherKeys[0].Right)
				{
					current_entity->AdjustPosition(sf::Vector2f(-1, 0));
					ColCheck(sf::Vector2f(2, 0));
					current_entity->AdjustJumpSpeed(-0.001);
					ColCheck(sf::Vector2f(0, 0.002));
				}
				else if (OtherKeys[0].Right && !OtherKeys[0].Left)
				{
					current_entity->AdjustPosition(sf::Vector2f(1, 0));
					ColCheck(sf::Vector2f(-2, 0));
					current_entity->SetJumpSpeed(-0.001);
					ColCheck(sf::Vector2f(0, 0.002));
				}

				OtherKeys.erase(OtherKeys.begin());
			}
		}

		if (players[currentPlayer]->GetCurrentEntity()->GetJumpSpeed() != 0)
		{
			players[currentPlayer]->GetCurrentEntity()->AdjustJumpSpeed(-(GRAVITY / 2));
			ColCheck(sf::Vector2f(0, -1));
			if (players[currentPlayer]->GetCurrentEntity()->GetJumpSpeed() != 0)
				players[currentPlayer]->GetCurrentEntity()->AdjustPosition(0, -players[currentPlayer]->GetCurrentEntity()->GetJumpSpeed());
	
			if (players[currentPlayer]->GetCurrentEntity()->GetYPosition() > 650)
				players[currentPlayer]->GetCurrentEntity()->SetJumpSpeed(0);

		}
		mut2.unlock();
		timer.restart();
	}
	else if (roundTimer.getElapsedTime().asSeconds() >= 10)
	{
		if (engineType == EngineType::Client)
			SendData();

		roundTimer.restart();
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
	std::vector<std::string> movesetData;
	for (int i = 0; i < cycleCounter; i++)
	{
		std::string data = "";
		if (players[currentPlayer]->GetKeyboardData(i, true, false))
			data += "U";
		else
			data += "_";

		if (players[currentPlayer]->GetKeyboardData(i, false, true))
			data += "L";
		else
			data += "_";
		
		if (players[currentPlayer]->GetKeyboardData(i, false, false))
			data += "R";
		else
			data += "_";

		movesetData.push_back(data);
	}

	ApplicationManager::getInstance().getNetworkManager()->sendMoveSetMsg(movesetData);
	cycleCounter = 0;
}

void IEngine::ReceiveData(std::vector<std::string> movesetData)
{
	switchplayerBence();

	for (int i = 0; movesetData.size(); i++)
	{
		bool up, left, right = false;

		up = movesetData[i][0] == 'U' || movesetData[i][1] == 'U' || movesetData[i][2] == 'U';
		left = movesetData[i][0] == 'L' || movesetData[i][1] == 'L' || movesetData[i][2] == 'L';
		right = movesetData[i][0] == 'R' || movesetData[i][1] == 'R' || movesetData[i][2] == 'R';

		players[currentPlayer]->AddKeyboardData(up, left, right);
	}

	OtherKeys = players[currentPlayer]->getKeyboardDataAsVector();
	for (int i = 0; i < OtherKeys.size(); i++)
	{
		LOG((OtherKeys[i].Left ? "L" : "_"));
		LOG((OtherKeys[i].Up ? "U" : "_"));
		LOG((OtherKeys[i].Right ? "R" : "_"));
	}
}

void IEngine::switchplayerBence()
{
	if (currentPlayer == 0) {
		currentPlayer = 1;
	}
	else {
		currentPlayer = 0;
	}
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

void IEngine::ColCheck(sf::Vector2f direction, bool gravCheck)
{
	if (Wizard* w = dynamic_cast<Wizard*>(players[currentPlayer]->GetCurrentEntity()->GetDrawable()))
	{
		Entity* currentEnt = players[currentPlayer]->GetCurrentEntity();
		sf::IntRect wizRec(w->get_x(), w->get_y(), 50, 50);
		Window* win = (Window*)(ApplicationManager::getInstance().getGuiManager().get());

		for (int i = 0; i < Blocks.size(); i++)
		{
			sf::IntRect blockRec(Blocks[i]->get_x(), Blocks[i]->get_y(), 50, 50);
			if (!blockRec.intersects(wizRec))
				continue;
			if (!Blocks[i]->is_alive())
				continue;
			if (w->wizard_in_block(Blocks[i]))
			{
				currentEnt->AdjustPosition(direction);
				currentEnt->AdjustPosition(-direction.x / 2, -direction.y / 2);
				currentEnt->SetJumpSpeed(0);
				break;
			}
		}
	}
}

void IEngine::GravCheck()
{
	//players[currentPlayer]->GetCurrentEntity()->SetJumping(true);
}

void IEngine::ReloadCollision()
{
	Window* win = (Window*)(ApplicationManager::getInstance().getGuiManager().get());
	blockRect.empty();
	for (std::shared_ptr<Block> b : win->get_map()->get_all_blocks())
	{
		sf::IntRect rec(b->get_x(), b->get_y() + BLOCK_SHIFT, 50, 50);
		blockRect.push_back(rec);
	}

	Blocks = win->get_map()->get_all_blocks();

	reloaded = true;
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

void IEngine::SetDefaultPlayer(int player, bool setCurrent)
{
	defaultPlayer = player;
	if (setCurrent)
		currentPlayer = player;
}
