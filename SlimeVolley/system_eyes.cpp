#include "system_eyes.h"

#include <cmath>
#include <iostream>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "constants.h"
#include "engine.h"
#include "entity.h"
#include "tags.h"

#define PI 3.14159265

void SystemEyes::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Iterate over all player entities and set eyes in right position
	// Get coords of ball
	
	int vec_1_x = cspr_ball->x - (cspr_player_1->x + PUPILS_OFFSET_X_1);
	int vec_1_y = cspr_ball->y- (cspr_player_1->y + PUPILS_OFFSET_Y);

	double vec_1_l = sqrt(vec_1_x*vec_1_x + vec_1_y*vec_1_y);

	vec_1_x = (int)((vec_1_x / vec_1_l)*RADIUS_EYES);
	vec_1_y = (int)((vec_1_y / vec_1_l)*RADIUS_EYES);

	vec_1_l = sqrt(vec_1_x*vec_1_x + vec_1_y*vec_1_y);

	int vec_2_x = cspr_ball->x - (cspr_player_2->x + PUPILS_OFFSET_X_2);
	int vec_2_y = cspr_ball->y - (cspr_player_2->y + PUPILS_OFFSET_Y);


	double vec_2_l = sqrt(vec_2_x*vec_2_x + vec_2_y*vec_2_y);

	vec_2_x = (int)((vec_2_x / vec_2_l)*RADIUS_EYES);
	vec_2_y = (int)((vec_2_y / vec_2_l)*RADIUS_EYES);

	cpla_player_1->pupil_x = cspr_player_1->x + PUPILS_OFFSET_X_1 + vec_1_x;
	cpla_player_1->pupil_y = cspr_player_1->y + PUPILS_OFFSET_Y + vec_1_y;

	cpla_player_2->pupil_x = cspr_player_2->x + PUPILS_OFFSET_X_2 + vec_2_x;
	cpla_player_2->pupil_y = cspr_player_2->y + PUPILS_OFFSET_Y + vec_2_y;
}


bool SystemEyes::Initialize()
{
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1)
		{
			cspr_player_1 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
			cpla_player_1 = (ComponentPlayer*)i->GetComponent(Component::PLAYER);
		}
		else if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 2)
		{
			cspr_player_2 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
			cpla_player_2 = (ComponentPlayer*)i->GetComponent(Component::PLAYER);
		}
	}

	entities = engine->GetEntityStream()->WithTag(Component::BALL);
	for each (Entity* i in entities)
	{
		cspr_ball = (ComponentSprite*)i->GetComponent(Component::SPRITE);
	}

	return true;
}
