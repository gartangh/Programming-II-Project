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
		// TODO: Update velocity and position of all entities with motion component
		Context* context = engine->GetContext();

		bool left_player1 = context->GetKeyPressed(ALLEGRO_KEY_Q, false);
		bool right_player1 = context->GetKeyPressed(ALLEGRO_KEY_D, false);
		bool up_player1 = context->GetKeyPressed(ALLEGRO_KEY_Z, false);

		bool left_player2 = context->GetKeyPressed(ALLEGRO_KEY_LEFT, false);
		bool right_player2 = context->GetKeyPressed(ALLEGRO_KEY_RIGHT, false);
		bool up_player2 = context->GetKeyPressed(ALLEGRO_KEY_UP, false);

		set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::MOTION);
		for each (Entity* i in entities)
		{
			ComponentMotion *comp_motion = (ComponentMotion*)i->GetComponent(Component::MOTION);
			ComponentSprite *comp_sprite = (ComponentSprite*)i->GetComponent(Component::SPRITE);

			comp_motion->v_x += comp_motion->a_x;
			comp_motion->v_y += comp_motion->a_y;

			if (comp_sprite->sprite == Graphics::SPRITE_PLAYER1) {
				comp_motion->v_x = left_player1*(-SLIME_V_X) + right_player1*(SLIME_V_X);
				if (up_player1 && comp_sprite->y < 1) {
					comp_motion->v_y = SLIME_V_Y;
				}
			}
			else if (comp_sprite->sprite == Graphics::SPRITE_PLAYER2) {
				comp_motion->v_x = left_player2*(-SLIME_V_X) + right_player2*(SLIME_V_Y);
				if (up_player2  && comp_sprite->y < 1) {
					comp_motion->v_y = SLIME_V_Y;
				}
			}

			comp_sprite->x += comp_motion->v_x;
			if (comp_sprite->sprite == Graphics::SPRITE_PLAYER2 || comp_sprite->sprite == Graphics::SPRITE_PLAYER1) {
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
