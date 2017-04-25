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
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	if (prev.x_ball != cspr_ball->x || prev.y_ball != cspr_ball->y ||
		prev.x_player_1 != cspr_player_1->x || prev.y_player_1 != cspr_player_1->y ||
		prev.x_player_2 != cspr_player_2->x || prev.y_player_2 != cspr_player_2->y) {

		prev = { cspr_player_1->x , cspr_player_1->y, cspr_player_2->x , cspr_player_2->y, cspr_ball->x , cspr_ball->y };
		cs.push_back(prev);
	}

	// Is there a winner?
	if (engine->GetContext()->GetState() >  0|| engine->GetContext()->print)
	{
		test = false;
		// TODO: Output coordinates to file
		time_t now = time(0);
		ofstream myfile;
		char intStr[33];
		_itoa_s(now, intStr, 10);

		string path = "assets/highscores/" + string(intStr) + "_";
		string filename = path + string(intStr) + string("_");
		
		char intStr2[2];

		engine->GetContext()->GetLevel();
		_itoa_s(engine->GetContext()->GetLevel(), intStr2, 10);
		std::cout << string(intStr2) << "\n";
		path += string(intStr2);
		path += string(".txt");

		std::cout << path << "\n";
		myfile.open(path);

		if (myfile.is_open()) {
			for (coordinates i : cs) {
				myfile << i.x_ball << " " << i.y_ball << " " << i.x_player_1 << " " << i.y_player_1 << " " << i.x_player_2 << " " << i.y_player_2 << "\n";
			}
			//myfile << "Writing hey to a file.\n";
			myfile.close();
		}
		else {
			std::cout << "couldn't open file\n";
		}
		
	}
}

bool SystemOutput::Initialize()
{
	// TODO: Initialize all component pointers (optional)
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

	return true;
}
