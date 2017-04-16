#include "engine.h"

#include <algorithm>

#include "allegro_lib.h"
#include "entity_stream.h"
#include "system.h"

void Engine::AddEntity(Entity* entity)
{
	entities.push_back(entity);
	es.EntityAdded(entity);
}

void Engine::RemoveEntity(Entity* entity)
{
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	vector<Entity*>::iterator it = entities.begin();
	while (it != entities.end())
	{
		if ((*it) == entity)
		{
			it = entities.erase(it);
			es.EntityRemoved(entity);
		}
		else
		{
			it++;
		}
	}
}

void Engine::AddSystem(System* system)
{
	system->SetEngine(this);
	systems.push_back(system);
}

void Engine::RemoveSystem(System* system)
{
	vector<System*>::iterator it = systems.begin();
	while (it != systems.end())
	{
		if ((*it) == system)
		{
			system->SetEngine(NULL);
			it = systems.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Engine::Update()
{
	for (vector<System*>::iterator it = systems.begin(); it != systems.end(); it++)
	{
		(*it)->Update();
	}
}

vector<Entity*> Engine::GetEntities()
{
	return entities;
}

Context* Engine::GetContext()
{
	return context;
}

EntityStream * Engine::GetEntityStream()
{
	return &es;
}

void Engine::setEntities(ComponentSprite* cspr_player_1, ComponentMotion* cmot_player_1, 
						 ComponentSprite* cspr_player_2, ComponentMotion* cmot_player_2, 
						 ComponentSprite* cspr_ball, ComponentMotion* cmot_ball) 
{
	SystemCollision* a = (SystemCollision*)systems.at(1);
	a->setBall(cspr_ball, cmot_ball);

	SystemAI* ai = (SystemAI*)systems.at(0);
	ai->setEntities(cspr_player_1, cspr_player_2, cmot_player_2, cspr_ball, cmot_ball);

	SystemStateSingle *single = (SystemStateSingle*)systems.at(11);
	single->setBall(cspr_ball);
}
