#include "stdafx.h"
#include "IEngine.h"


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

void IEngine::IsInputPressed(int keycode)
{
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
