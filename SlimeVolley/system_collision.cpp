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

			double distance = (player->x - co_ball_x)*(player->x - co_ball_x) + (player->y - co_ball_y)*(player->y - co_ball_y);

			if (distance < 46.875*46.845) {
				HandleBallPlayerCollision(player, player_mot);
			}

			if (player->x < RADIUS_SLIME || player->x > GAME_WIDTH - RADIUS_SLIME) {
				HandlePlayerWallCollision(player, player_mot);
			}
		}
	
		if (co_ball_y < RADIUS_BALL) {
			double lost_energy = -0.8;
			cmot_ball->v_y *= lost_energy;
			/*
			if (co_ball_y < 10 + GROUND && cmot_ball->v_y < .5) {
				cspr_ball->y = GROUND;
			}
			else {
				
			}*/
			
		}

		if (co_ball_x < RADIUS_BALL || co_ball_x > 750 - RADIUS_BALL) {
			HandleBallWallCollision();
		}
		if (co_ball_y < 49 && co_ball_y> 0 && abs(co_ball_x - MIDDLE) < RADIUS_BALL) {
			HandleBallNetCollision();
		}
		//if(player)
		
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
	// TODO: Handle a possible collision between a player and the walls/floor

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

	//place ball outsite collision circle
	cspr_ball->x += v_x_n*SETBACK;
	cspr_ball->y += v_y_n*SETBACK;

	//set speed
	cmot_ball->v_x = v_x_n*BOUNCINESS;
	cmot_ball->v_y = v_y_n*BOUNCINESS;

	/*
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
	*/
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
		else if (((ComponentPlayer*)i->GetComponent(Component::MOTION))->player_id == 2)
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
