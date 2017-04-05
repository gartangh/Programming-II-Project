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
#include "keyenum.h"

#define SPEED 100

void SystemMotion::Update()
{
	// Is the game running?
	if (!engine->GetContext()->IsPaused() && !engine->GetContext()->IsFrozen())
	{
		// TODO: Update velocity and position of all entities with motion
		// component
		Context* con = engine->GetContext();
		bool left_player_one = con->GetKeyPressed(QKEY, false);
		bool right_player_one = con->GetKeyPressed(DKEY, false);
		bool left_player_two = con->GetKeyPressed(LEFTKEY, false);
		bool right_player_two = con->GetKeyPressed(RIGHTKEY, false);

		double time = 1.0 / 40;
		set<Entity*> entities= engine->GetEntityStream()->WithTag(Component::MOTION);
		for (set<Entity*>::iterator i = entities.begin(); i != entities.end(); i++) {
			ComponentMotion *motion_comp = (ComponentMotion*)(*i)->GetComponent(Component::MOTION);
			ComponentSprite *sprite_comp = (ComponentSprite*)(*i)->GetComponent(Component::SPRITE);
			if (sprite_comp->sprite == Graphics::SPRITE_PLAYER1) {
				motion_comp->v_x = left_player_one*(-SPEED) + right_player_one*(SPEED);
			}
			if (sprite_comp->sprite == Graphics::SPRITE_PLAYER2) {
				motion_comp->v_x = left_player_two*(-SPEED) + right_player_two*(SPEED);
			}
			sprite_comp->x += motion_comp->v_x*time;
			sprite_comp->y += motion_comp->v_y*time;
			motion_comp->v_x += motion_comp->a_x*time;
			motion_comp->v_y += motion_comp->a_y*time;
		}
	}
}
