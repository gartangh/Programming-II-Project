#define NOMINMAX

#include "system_replay.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "component.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "tags.h"

void SystemReplay::Update()
{
	// Initialize (required)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// TODO: According to toggled keys in context, either:
	//   [ARROW_LEFT] Decrease playout speed by factor 2
	//	 [ARROW_RIGHT] Increase playout speed by factor 2
	//   [ARROW_UP] Go to next point
	//	 [ARROW_DOWN] Go to next level
	//	 [P] Pause playout
	//	 [ESC] Return to menu

	// Is the game running?
	if (!engine->GetContext()->IsPaused())
	{
		GoToNextFrame();
	}
}

void SystemReplay::GoToNextFrame()
{
	frame += speed;

	if (frame < cs.size()) {
		cspr_player_1->x = cs.at(frame).x_player_1;
		cspr_player_1->y = cs.at(frame).y_player_1;

		cspr_player_2->x = cs.at(frame).x_player_2;
		cspr_player_2->y = cs.at(frame).y_player_2;

		cspr_ball->x = cs.at(frame).x_ball;
		cspr_ball->y = cs.at(frame).y_ball;
	}
}

void SystemReplay::GoToNextPoint()
{
	while (status < 1)
	{
		GoToNextFrame();
	}
}

void SystemReplay::GoToNextLevel()
{
	while (status < 2)
	{
		GoToNextFrame();
	}
}

bool SystemReplay::Initialize()
{
	frame = 0;
	speed = 1;
	// TODO: Read input coordinates from file and push to list
	std::string inputfile  = engine->GetContext()->GetInputFile();
	std::cout << inputfile;
	string line;
	std::fstream myfile(inputfile, std::ios_base::in);
	if (myfile.is_open())
	{
		
		float a;
		while (myfile >> a)
		{
			printf("%f ", a);
		}

		getchar();
	}

	else cout << "Unable to open file";
	
	// TODO: Initialize all component pointers (optional)
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1) {
			cspr_player_1 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
		}
		else if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 2) {

			cspr_player_2 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
		}
	}

	entities = engine->GetEntityStream()->WithTag(Component::BALL);
	for each (Entity* i in entities)
	{
		cspr_ball = (ComponentSprite*)i->GetComponent(Component::SPRITE);
	}

	return true;
}
