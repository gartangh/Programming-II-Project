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
		AddSystem(new SystemAI());
		AddSystem(new SystemCollision());
		AddSystem(new SystemEyes());
		AddSystem(new SystemInputMulti());
		AddSystem(new SystemInputSingle());
		AddSystem(new SystemMotion());
		AddSystem(new SystemOutput());
		AddSystem(new SystemPoints());
		AddSystem(new SystemRender());
		AddSystem(new SystemReplay());
		AddSystem(new SystemStateMulti());
		AddSystem(new SystemStateSingle());
	};

	~Engine()
	{
	};

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void AddSystem(System* system);
	void RemoveSystem(System* system);
	void Update();
	vector<Entity*> GetEntities();
	Context* GetContext();
	EntityStream* GetEntityStream();
	void setBall(ComponentSprite* sprite_ball, ComponentMotion* motion_ball);
	
private:
	vector<Entity*> entities;
	vector<System*> systems;
	Context* context;
	EntityStream es;
};
