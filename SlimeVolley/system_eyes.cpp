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
	/*
	// TODO: Iterate over all player entities and set eyes in right position
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::SPRITE);

	set<Entity*> ball = engine->GetEntityStream()->WithTag(Component::BALL);
	ComponentSprite *ballsprite = (ComponentSprite*)(*ball.begin())->GetComponent(Component::SPRITE);
	int co_x_b = ballsprite->x;
	int co_y_b = ballsprite->y;

	set<Entity*> players = engine->GetEntityStream()->WithTag(Component::PLAYER);
	ComponentSprite *playersSprite = (ComponentSprite*)(*ball.begin())->GetComponent(Component::SPRITE);
	int co_x_p1 = playersSprite->x;
	int co_y_p1= playersSprite->y;

	playersSprite = (ComponentSprite*)(*ball.end())->GetComponent(Component::SPRITE);
	int co_x_p2 = playersSprite->x;
	int co_y_p2 = playersSprite->y;

	int dX = co_x_b - co_x_p1;
	int dY = co_y_b - co_y_p1;

	double angle1 = atan(dY / dX);
	if (angle1 < 0) angle1 += PI / 2;

	dX = co_x_b - co_x_p2;
	dY = co_y_b - co_y_p2;

	double angle2 = atan(dY / dX);
	if (angle2 < 0) angle2 += PI / 2;


	for (set<Entity*>::iterator i = entities.begin(); i != entities.end(); i++) {
		ComponentSprite *sprite_comp = (ComponentSprite*)(*i)->GetComponent(Component::SPRITE);
		if (sprite_comp->sprite == Graphics::SPRITE_PUPIL) {
			int co_x = sprite_comp->x;
			int co_y = sprite_comp->y;
			int dX = co_x_b - co_x;
			int dY = co_y_b - co_y;

			double angle = atan(dY / dX);

		}
		
	}
	*/
}

bool SystemEyes::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
