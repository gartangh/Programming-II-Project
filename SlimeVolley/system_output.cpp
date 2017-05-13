#include "system_output.h"

#include <fstream>
#include <iostream>
#include <list>
#include <ctime>

#include "component_player.h"
#include "component_sprite.h"
#include "context.h"
#include "engine.h"

void SystemOutput::Update()
{
	// Initialize
	if (!initialized)
	{
		initialized = Initialize();
	}

	if (prev.x_ball != cspr_ball->x			|| prev.y_ball != cspr_ball->y			||
		prev.x_player_1 != cspr_player_1->x || prev.y_player_1 != cspr_player_1->y	||
		prev.x_player_2 != cspr_player_2->x || prev.y_player_2 != cspr_player_2->y	)
	{
		prev = { cspr_player_1->x , cspr_player_1->y, cspr_player_2->x , cspr_player_2->y, cspr_ball->x , cspr_ball->y };
		cs.push_back(prev);
	}
	
	// Is there a winner?
	if (engine->GetContext()->GetState() > 0 || engine->GetContext()->print)
	{
		std::string file_name = "./assets/highscores/" + std::to_string(start_time) + "_" + std::to_string(level) + ".txt";
		ofstream myfile(file_name);

		if (myfile.is_open()) {
			for (coordinates i : cs) {
				myfile << i.x_player_1 << " " << i.y_player_1 << " " << i.x_player_2 << " " << i.y_player_2 << " " << i.x_ball << " " << i.y_ball << endl;
			}
			
			myfile.close();
		}
		else {
			std::cout << "couldn't open file" << endl;
		}
	}
}

bool SystemOutput::Initialize()
{
	// Initialize all component pointers (optional)
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1)
		{
			cspr_player_1 = (ComponentSprite*)i->GetComponent(Component::SPRITE);

		}
		else if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 2)
		{
			cspr_player_2 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
		}
	}

	entities = engine->GetEntityStream()->WithTag(Component::BALL);
	for each (Entity* i in entities)
	{
		cspr_ball = (ComponentSprite*)i->GetComponent(Component::SPRITE);
	}

	prev = { 0,0,0,0,0,0 };
	start_time = engine->GetContext()->GetStartTime();
	level = engine->GetContext()->GetLevel();

	return true;
}
