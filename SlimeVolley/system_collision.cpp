#define NOMINMAX

#include "system_collision.h"

#include <algorithm>
#include <cmath>
#include <set>
#include <iostream>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "component_ball.h"
#include "constants.h"
#include "engine.h"
#include "entity.h"
#include "constants.h"

#define SETBACK (.2)

void SystemCollision::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	if (!engine->GetContext()->IsPaused() && !engine->GetContext()->IsFrozen())
	{
		// TODO: Handle all possible collisions
		// Collision between Player 1 and ball
		double distance_player_1 = (cspr_player_1->x - cspr_ball->x)*(cspr_player_1->x - cspr_ball->x) + (cspr_player_1->y - cspr_ball->y)*(cspr_player_1->y - cspr_ball->y);
		if (distance_player_1 < RADIUS_COLLISION*RADIUS_COLLISION) {
			HandleBallPlayerCollision(cspr_player_1, cmot_player_1);
		}

		// Collision between Player 1 and wall
		if (cspr_player_1->x <= RADIUS_SLIME || cspr_player_1->x >= MIDDLE - RADIUS_SLIME) {
			HandlePlayerWallCollision(cspr_player_1, cmot_player_1);
		}


		// Collision between Player 2 and ball
		double distance_player_2 = (cspr_player_2->x - cspr_ball->x)*(cspr_player_2->x - cspr_ball->x) + (cspr_player_2->y - cspr_ball->y)*(cspr_player_2->y - cspr_ball->y);
		if (distance_player_2 < RADIUS_COLLISION*RADIUS_COLLISION) {
			HandleBallPlayerCollision(cspr_player_2, cmot_player_2);
		}

		// Collision between Player 2 and wall
		if (cspr_player_2->x <= MIDDLE + RADIUS_SLIME || cspr_player_2->x >= GAME_WIDTH - RADIUS_SLIME) {
			HandlePlayerWallCollision(cspr_player_2, cmot_player_2);
		}

		// Collision between ball and wall
		if (cspr_ball->x< RADIUS_BALL || cspr_ball->x > 750 - RADIUS_BALL) {
			HandleBallWallCollision();
		}

		// Collision between ball and net
		if (cspr_ball->y < 49 && abs(cspr_ball->x - MIDDLE) < RADIUS_BALL) {
			HandleBallNetCollision();
		}		
	}
}

void SystemCollision::HandleBallWallCollision()
{
	// TODO: Handle a possible collision between the ball and a wall
	cmot_ball->v_x *= -1;
}

void SystemCollision::HandleBallNetCollision()
{
	// TODO: Handle a possible collision between the ball and the net
	cmot_ball->v_x = 0;
}

void SystemCollision::HandlePlayerWallCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	// TODO: Handle a possible collision between a player and the walls / floor
	if (csprPlayer->y <= RADIUS_SLIME) {
		cmotPlayer->v_y = 0;
	}

	if (csprPlayer->x <= RADIUS_SLIME || csprPlayer->x >= GAME_WIDTH - RADIUS_SLIME) {
		cmotPlayer->v_x = 0;
	}
}

void SystemCollision::HandleBallPlayerCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	int player_x = csprPlayer->x;
	int player_y = csprPlayer->y;

	int ball_x = cspr_ball->x;
	int ball_y = cspr_ball->y;

	double normal_x = ball_x - player_x;
	double normal_y = ball_y - player_y;

	double v_x = cmot_ball->v_x;
	double v_y = cmot_ball->v_y;


	//orhtogonal projection houden
	double dist = normal_x*normal_x + normal_y*normal_y;
	double v_n = normal_x*v_x + normal_y*v_y;
	double o_x = (v_n / dist)*normal_x;
	double o_y = (v_n / dist)*normal_y;

	//rejectie inverteren
	double p_x = (v_x - o_x);
	double p_y = (v_y - o_y);

	double v_x_n = -o_x + p_x;
	double v_y_n = -o_y + p_y;

	double v_l = sqrt(v_x_n*v_x_n + v_y_n*v_y_n);

	//set speed
	cmot_ball->v_x = v_x_n*BOUNCINESS + cmotPlayer->v_x;
	cmot_ball->v_y = v_y_n*BOUNCINESS + cmotPlayer->v_y;


	int d_x = ball_x - player_x;
	int d_y = ball_y - player_y;

	//double dist = sqrt(d_x*d_x + d_y + d_y);
	/*
	double dist_diff = COLLISION_BUFFER*RADIUS_COLLISION;

	v_x_n /= v_l;
	v_y_n /= v_l;

	cspr_ball->x = v_x_n*dist_diff;
	cspr_ball->y = v_y_n*dist_diff;
	*/

	COLLISION_BUFFER;
	
}

bool SystemCollision::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1)
		{
			cspr_player_1 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
			cmot_player_1 = (ComponentMotion*)i->GetComponent(Component::MOTION);

		}
		else if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 2)
		{
			cspr_player_2 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
			cmot_player_2 = (ComponentMotion*)i->GetComponent(Component::MOTION);
		}
	}

	entities = engine->GetEntityStream()->WithTag(Component::BALL);
	for each (Entity* i in entities)
	{
		cspr_ball = (ComponentSprite*)i->GetComponent(Component::SPRITE);
		cmot_ball = (ComponentMotion*)i->GetComponent(Component::MOTION);
	}

	return true;
}
