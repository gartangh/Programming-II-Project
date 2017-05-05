#pragma once

#include <map>
#include <vector>

#include "context.h"
#include "entity.h"
#include "entity_stream.h"
#include "system.h"
#include "allSystems.h"
using namespace std;

class Engine
{
public:
	Engine(Context* _context) : context(_context)
	{
	};

	~Engine()
	{
		for (int i = 0; i < entities.size(); i++) {
			delete entities.at(i);
		}
		for (int i = 0; i < systems.size(); i++) {
			delete systems.at(i);
		}
	};

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void AddSystem(System* system);
	void RemoveSystem(System* system);
	void Update();
	vector<Entity*> GetEntities();
	Context* GetContext();
	EntityStream* GetEntityStream();
	
private:
	vector<Entity*> entities;
	vector<System*> systems;
	Context* context;
	EntityStream es;
};
