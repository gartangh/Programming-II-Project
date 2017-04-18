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

			// Update velocity
			comp_motion->v_x += comp_motion->a_x;
			comp_motion->v_y += comp_motion->a_y;

			// Update coords
			comp_sprite->x += comp_motion->v_x;
			if (comp_sprite->sprite == Graphics::SPRITE_PLAYER1 || comp_sprite->sprite == Graphics::SPRITE_PLAYER2) {
				int co_y = comp_sprite->y + comp_motion->v_y;
				if (co_y < 0) {
					comp_sprite->y = 0;
					comp_motion->v_y = 0;
				}
				else {
					comp_sprite->y = co_y;
				}
			}
			else {
				comp_sprite->y += comp_motion->v_y;
			}
		}
	}
}
