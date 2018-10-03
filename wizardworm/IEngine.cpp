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

Entity * IEngine::GetEntity(int pos)
{
	if (entities.size() > pos)
		return nullptr;
	if (pos < 0)
		return nullptr;
	return &(entities[pos]);
}

void IEngine::AddEntity(Entity & entity)
{
	entities.push_back(entity);
}
