#define NOMINMAX

#include "system_motion.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "tags.h"

void SystemMotion::Update()
{
	// Is the game running?
	if (!engine->GetContext()->IsPaused() && !engine->GetContext()->IsFrozen())
	{
		// TODO: Update velocity and position of all entities with motion component
		Context* context = engine->GetContext();

		set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::MOTION);
		for each (Entity* i in entities)
		{	
			// Get components
			ComponentMotion *comp_motion = (ComponentMotion*)i->GetComponent(Component::MOTION);
			ComponentSprite *comp_sprite = (ComponentSprite*)i->GetComponent(Component::SPRITE);
			ComponentPlayer *comp_player = (ComponentPlayer*)i->GetComponent(Component::PLAYER);

			// Update velocity
			comp_motion->v_x += comp_motion->a_x;
			comp_motion->v_y += comp_motion->a_y;

			// Update coords
			
			if (comp_player != nullptr)
			{
				//PLAYER
				int co_y = comp_sprite->y + comp_motion->v_y;
				if (comp_sprite->x < MIDDLE) {
					if (!(comp_sprite->x < RADIUS_SLIME && comp_motion->v_x < 0)) {
						comp_sprite->x += comp_motion->v_x;
					}
				}
				else {
					if (!(comp_sprite->x > GAME_WIDTH - RADIUS_SLIME && comp_motion->v_x > 0)) {
						comp_sprite->x += comp_motion->v_x;
					}

				}
				//comp_sprite->x += comp_motion->v_x;
				if (co_y <= 0)
				{
					comp_sprite->y = 0;
					comp_motion->v_y = 0;
				}
				else {
					comp_sprite->y = co_y;
				}
					
			}
			else
				//BALL
				comp_sprite->x += comp_motion->v_x;
				comp_sprite->y += comp_motion->v_y;
		}
	}
}
