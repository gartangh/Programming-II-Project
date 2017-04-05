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
		System *a = new SystemAI(); 
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemCollision();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemEyes();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemInputMulti();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemInputSingle();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemMotion();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemOutput();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemPoints();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemRender();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemReplay();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemStateMulti();
		a->SetEngine(this);
		systems.push_back(a);
		a = new SystemStateSingle();
		a->SetEngine(this);
		systems.push_back(a);
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

private:
	vector<Entity*> entities;
	vector<System*> systems;
	Context* context;
	EntityStream es;
};
