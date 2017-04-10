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

void SystemCollision::setBall(ComponentSprite* sprite_comp, ComponentMotion* motion_comp) {
	cspr_ball = sprite_comp;
	cmot_ball = motion_comp;
}

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
		set<Entity*> ball_set = engine->GetEntityStream()->WithTag(Component::BALL);
		set<Entity*> players_set = engine->GetEntityStream()->WithTag(Component::PLAYER);
		//std::cout << "size: " << players_set.size();
		ComponentSprite* ball = (ComponentSprite*)((*ball_set.begin())->GetComponent(Component::SPRITE));

		int co_ball_x = ball->x;
		int co_ball_y = ball->y;

		for (set<Entity*>::iterator i = players_set.begin(); i != players_set.end(); i++){
			ComponentSprite* player = (ComponentSprite*)((*i)->GetComponent(Component::SPRITE));
			ComponentMotion* player_mot = (ComponentMotion*)((*i)->GetComponent(Component::MOTION));

			double distance = sqrt((player->x - co_ball_x)*(player->x - co_ball_x) + (player->y - co_ball_y)*(player->y - co_ball_y));

			if (distance < 46.875) {
				HandleBallPlayerCollision(player, player_mot);
			}
		}
	
		if (co_ball_y < RADIUS_BALL) {

		}

		if (co_ball_x < RADIUS_BALL || co_ball_x > 750 - RADIUS_BALL) {
			HandleBallWallCollision();
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

}

void SystemCollision::HandlePlayerWallCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{
	// TODO: Handle a possible collision between a player and the walls/floor

}

void SystemCollision::HandleBallPlayerCollision(ComponentSprite* csprPlayer, ComponentMotion* cmotPlayer)
{



	
	double d_x = cspr_ball->x - csprPlayer->x;
	double d_y = cspr_ball->y - csprPlayer->y;
	double dist = std::sqrt(d_x * d_x + d_y * d_y);
	double radius = 46.875;
	if (d_y > 0 && dist < radius)
	{
		
		cspr_ball->x = csprPlayer->x + radius * d_x / dist;
		cspr_ball->y = csprPlayer->y + radius * d_y / dist;

		double d_v_x = cmot_ball->v_x - cmotPlayer->v_x;
		double d_v_y = cmot_ball->v_y - cmotPlayer->v_y;

		//?
		double s = (d_x * d_v_x + d_y * d_v_y * 2) / dist;

		if (s < 0)
		{
			cmot_ball->v_x += cmotPlayer->v_x - 2 * d_x * s / dist;
			cmot_ball->v_y += cmotPlayer->v_y - d_y * s / dist;

			//if Vx ball smaller then -11.25 set to 11.25
			//if Vx ball bigger then 11.25 set to 11.25
			cmot_ball->v_x = std::max(cmot_ball->v_x, -11.25);
			cmot_ball->v_x = std::min(cmot_ball->v_x, 11.25);

			//if Vy ball smaller then -8.75 set to 8.75
			//if Vy ball bigger then 8.75 set to 8.75
			cmot_ball->v_y = std::max(cmot_ball->v_y, -8.25);
			cmot_ball->v_y = std::min(cmot_ball->v_y, 8.25);
		}
	}
	
}

bool SystemCollision::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
