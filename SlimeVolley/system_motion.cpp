#define NOMINMAX

#include "system_motion.h"

#include <algorithm>
#include <cmath>

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
		// TODO: Update velocity and position of all entities with motion
		// component
		double time = 1.0 / 40;
		set<Entity*> entities= engine->GetEntityStream()->WithTag(Component::MOTION);
		for (set<Entity*>::iterator i = entities.begin(); i != entities.end(); i++) {
			ComponentMotion *motion_comp = (ComponentMotion*)(*i)->GetComponent(Component::MOTION);
			ComponentSprite *sprite_comp = (ComponentSprite*)(*i)->GetComponent(Component::SPRITE);
			sprite_comp->x += motion_comp->v_x*time;
			sprite_comp->y += motion_comp->v_y*time;
			motion_comp->v_x += motion_comp->a_x*time;
			motion_comp->v_y += motion_comp->a_y*time;
		}
	}
}
