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
		// TODO: Go to the next frame(s), if necessary
	}
}

void SystemReplay::GoToNextFrame()
{
	// TODO: Go to next frame by setting the new coordinates. Set state to:
	//   0 if a normal frame has been found
	//   1 if a frame has been found in which the ball has dropped
	//   2 if there are no coordinates left
	// and update the context whenever necessary

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
	// TODO: Read input coordinates from file and push to list
	std::string inputfile  = engine->GetContext()->GetInputFile();
	std::string line;
	ofstream myfile;
	myfile.open(inputfile);

<<<<<<< HEAD
	if (myfile.is_open()) {
		/*
		std::ifstream infile(inputfile);
		double x_ball;
		double y_ball;
		double x_player1;
		double y_player1;
		double x_player2;
		double y_player2;
		while (infile >> x_ball >> y_ball >> x_player1 >> y_player1 >> x_player2 >> y_player2) {
			coordinates a = {x_player1, y_player1, x_player2, y_player2, x_ball, y_ball};
			cs.push_back(a);
		}
		std::cout << "loaded coordinates, length: " << cs.size();
		*/
		myfile.close();
	}
	else {
		std::cout << "file couldn't be openend, system replay";
	}
	
	

	//set entities
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1)
		{
			cspr_player_1 = (ComponentSprite*)i->GetComponent(Component::SPRITE);

		}
		else if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 2)
		{
=======
	// TODO: Initialize all component pointers (optional)
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1) {
			cspr_player_1 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
		}
		else if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 2) {
>>>>>>> refs/remotes/origin/master
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
