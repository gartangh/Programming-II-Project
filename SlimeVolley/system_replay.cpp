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
	// Initialize
	if (!initialized)
	{
		initialized = Initialize();
	}

	// According to toggled keys in context, either:
	//   [ARROW_LEFT] Decrease playout speed by factor 2
	//	 [ARROW_RIGHT] Increase playout speed by factor 2
	//   [ARROW_UP] Go to next point
	//	 [ARROW_DOWN] Go to next level
	//	 [P] Pause playout
	//	 [ESC] Return to menu
	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_LEFT, true) && speed > .5)
	{
		speed /= 2.0;
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_RIGHT, true) && speed < 2.0)
	{
		speed *= 2.0;
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_UP, true))
	{
		GoToNextPoint();
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_DOWN, true))
	{
		GoToNextLevel();
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_P, true))
	{
		if (!engine->GetContext()->IsPaused()) {
			engine->GetContext()->SetPaused(true);
		}
		else {
			engine->GetContext()->SetPaused(false);
		}
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_ESCAPE, true))
	{
		// TODO: Exit
		engine->GetContext()->SetState(2);
		status = 0;
		initialized = false;
	}

	// Is the game running?
	if (!engine->GetContext()->IsPaused())
	{
		// Go to the next frame(s), if necessary
		if (status <= 1)
		{
			if (speed >= 2.0)
			{
				cs.pop_front();
				GoToNextFrame();
			}
			else if (speed <= .5 && pop)
			{
				pop = false;
				GoToNextFrame();
			}
			else if (speed <= .5 && !pop)
			{
				pop = true;
			}
			else {
				GoToNextFrame();
			}
		}
		else {
			engine->GetContext()->SetState(1);
			engine->GetContext()->ResetPoints();
			initialized = false;
		}
	}
}

void SystemReplay::GoToNextFrame()
{
	// Go to next frame by setting the new coordinates. Set status to:
	//   0 if a normal frame has been found
	//   1 if a frame has been found in which the ball has dropped
	//   2 if there are no coordinates left
	// and update the context whenever necessary
	coordinates a = cs.front();
	cs.pop_front();

	cspr_player_1->x = a.x_player_1;
	cspr_player_1->y = a.y_player_1;
	cspr_player_2->x = a.x_player_2;
	cspr_player_2->y = a.y_player_2;
	cspr_ball->x = a.x_ball;
	cspr_ball->y = a.y_ball;

	if (cs.empty())
	{
		status = 2;
	}
	else if (a.y_ball <= RADIUS_BALL)
	{
		status = 1;

		if (cspr_ball->x >= MIDDLE)
		{
			engine->GetContext()->IncreasePoints(1);
			engine->GetContext()->UpdateScore(200);
		}
		else
		{
			engine->GetContext()->IncreasePoints(2);
			engine->GetContext()->UpdateScore(-100);
		}
	}
	else
	{
		status = 0;
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
	// Read input coordinates from file and push to list
	std::ifstream input(engine->GetContext()->GetInputFile());

	if (input.is_open()) {
		double x_player1;
		double y_player1;
		double x_player2;
		double y_player2;
		double x_ball;
		double y_ball;
	
		while (input >> x_player1 >> y_player1 >> x_player2 >> y_player2 >> x_ball >> y_ball) {
			coordinates a = {x_player1, y_player1, x_player2, y_player2, x_ball, y_ball};
			cs.push_back(a);
		}
		
		input.close();
	}
	else {
		std::cout << "file couldn't be openend, system replay" << endl;
	}
	
	// Initialize all component pointers
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

	speed = 1.0;
	status = 0;
	pop = true;

	return true;
}
