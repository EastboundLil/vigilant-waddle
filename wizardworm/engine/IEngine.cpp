#include "stdafx.h"
#include "IEngine.h"

#define MOVING_SPEED 5
#define JUMPING_SPEED 10
#define GRAVITY 1


IEngine::IEngine()
{
}


IEngine::~IEngine()
{
}

void IEngine::Update()
{
	for (Entity& e : entities)
		e.Update();
}

void IEngine::Move(bool left, bool jumping)
{
	if (left)
		selectedEntity->SetSpeed(sf::Vector2f(-MOVING_SPEED, 0));
	else
		selectedEntity->SetSpeed(sf::Vector2f(MOVING_SPEED, 0));

	if (jumping && selectedEntity->GetSpeed().y == 0)
	{
		selectedEntity->AjdustSpeed(sf::Vector2f(0, JUMPING_SPEED));
		selectedEntity->AdjustAcceleration(sf::Vector2f(0, -GRAVITY));
	}
}

Entity * IEngine::GetEntity(int id)
{
	for (Entity e : entities)
	{
		if (e.GetId() == id)
			return &e;
	}

	return nullptr;
}

int IEngine::GetEntityCount()
{
	return entities.size();
}

void IEngine::AddEntity(Entity & entity)
{
	entities.push_back(entity);
}

void IEngine::AddEntity(Drawable * drawable, int Id)
{
	if (Id < 0)
	{
		Entity ent;
		ent.SetSprite(drawable);
		entities.push_back(ent);
	}
	else
	{
		Entity ent(Id);
		ent.SetSprite(drawable);
		entities.push_back(ent);
	}
}
