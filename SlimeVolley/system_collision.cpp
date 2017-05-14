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
		if (distance_player_1 < RADIUS_COLLISION*RADIUS_COLLISION)
			HandleBallPlayerCollision(cspr_player_1, cmot_player_1);

		// Collision between Player 2 and ball
		double distance_player_2 = (cspr_player_2->x - cspr_ball->x)*(cspr_player_2->x - cspr_ball->x) + (cspr_player_2->y - cspr_ball->y)*(cspr_player_2->y - cspr_ball->y);
		if (distance_player_2 < RADIUS_COLLISION*RADIUS_COLLISION)
			HandleBallPlayerCollision(cspr_player_2, cmot_player_2);

		//WALL collisions
		// Collision between Player 2 and wall
		if (cspr_player_2->x <= MIDDLE + RADIUS_SLIME || cspr_player_2->x >= GAME_WIDTH - 32)
			HandlePlayerWallCollision(cspr_player_2, cmot_player_2);

		// Collision between Player 1 and wall
		if (cspr_player_1->x <= RADIUS_SLIME || cspr_player_1->x >= MIDDLE - 32)
			HandlePlayerWallCollision(cspr_player_1, cmot_player_1);

		// Collision between ball and wall
		if (cspr_ball->x< RADIUS_BALL || cspr_ball->x > 750 - RADIUS_BALL)
			HandleBallWallCollision();

		// Collision between ball and net
		if (cspr_ball->y < 49 + RADIUS_BALL && abs(cspr_ball->x - MIDDLE) < RADIUS_BALL + 2)
			HandleBallNetCollision();
	}
}

void SystemCollision::HandleBallWallCollision()
{
	if (cspr_ball->x < MIDDLE && cmot_ball->v_x < 0)
		cmot_ball->v_x *= -1;
	if(cspr_ball->x > MIDDLE && cmot_ball->v_x > 0)
		cmot_ball->v_x *= -1;
}

void SystemCollision::HandleBallNetCollision()
{
	cmot_ball->v_x = 0;
	cspr_ball->y = RADIUS_BALL - 1;
}

void SystemCollision::HandlePlayerWallCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	if (csprPlayer->y <= RADIUS_SLIME)
		cmotPlayer->v_y = 0;

	if (csprPlayer->x <= RADIUS_SLIME && cmotPlayer->v_x < 0)
		cmotPlayer->v_x = 0;

	if (csprPlayer->x >= GAME_WIDTH - RADIUS_SLIME && cmotPlayer->v_x > 0)
		cmotPlayer->v_x = 0;
}

void SystemCollision::HandleBallPlayerCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	double d_x = cspr_ball->x - csprPlayer->x;
	double d_y = cspr_ball->y - csprPlayer->y;
	double dist = std::sqrt(d_x * d_x + d_y * d_y);
	if (d_y > 0 && dist < 46.875)
	{
		cspr_ball->x = csprPlayer->x + 46.875 * d_x / dist;
		cspr_ball->y = csprPlayer->y + 46.875 * d_y / dist;
		double d_v_x = cmot_ball->v_x - cmotPlayer->v_x;
		double d_v_y = cmot_ball->v_y - cmotPlayer->v_y;
		double s = (d_x * d_v_x + d_y * d_v_y * 2) / dist;
		if (s < 0)
		{
			cmot_ball->v_x += cmotPlayer->v_x - 2 * d_x * s / dist;
			cmot_ball->v_y += cmotPlayer->v_y - d_y * s / dist;
			cmot_ball->v_x = std::max(cmot_ball->v_x, -11.25);
			cmot_ball->v_x = std::min(cmot_ball->v_x, 11.25);
			cmot_ball->v_y = std::max(cmot_ball->v_y, -8.25);
			cmot_ball->v_y = std::min(cmot_ball->v_y, 8.25);
		}
	}
}

bool SystemCollision::Initialize()
{
	// Initialize all component pointers
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
