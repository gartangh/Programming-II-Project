#include "system_eyes.h"

#include <cmath>

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
	set<Entity*> ball = engine->GetEntityStream()->WithTag(Component::BALL);
	ComponentSprite *ballsprite = (ComponentSprite*)(*ball.begin())->GetComponent(Component::SPRITE);
	int co_x_ball = ballsprite->x + ballsprite->x_off;
	int co_y_ball = ballsprite->y + ballsprite->y_off;

	set<Entity*> players = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* player in players)
	{
		ComponentPlayer* comp_player = (ComponentPlayer*)player->GetComponent(Component::PLAYER);
		ComponentSprite* comp_sprite = (ComponentSprite*)player->GetComponent(Component::SPRITE);
		// Get coords of players's eyes
		int co_x_eye;
		if (comp_player->player_id = 1) {
			co_x_eye = comp_sprite->x + comp_sprite->x_off + PUPILS_OFFSET_X_1;
		}
		else if (comp_player->player_id = 2) {
			co_x_eye = comp_sprite->x + comp_sprite->x_off + PUPILS_OFFSET_X_2;
		}
		else continue;
		int co_y_eye = comp_sprite->y + comp_sprite->y_off + PUPILS_OFFSET_Y;

		// Calc rico
		int dX = co_x_ball - co_x_eye;
		int dY = co_y_ball - co_y_eye;

		double angle = atan(dY / dX);

		// Set pos of pupils
		comp_player->pupil_x = co_x_eye + cos(angle) * 2;
		comp_player->pupil_y = co_y_eye + sin(angle) * 2;
	}
}

bool SystemEyes::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
