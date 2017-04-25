#include "system_input_multi.h"

#include "allegro_lib.h"
#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "engine.h"

void SystemInputMulti::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Change players' movement, pause and exit according to toggled
	// keys in context
	pressed_left = engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_LEFT, false);
	pressed_right = engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_RIGHT, false);
	pressed_up = engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_UP, false);
	pressed_a = engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_A, false) | engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_Q, false);
	pressed_d = engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_D, false);
	pressed_w = engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_W, false) | engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_Z, false);
	
	cmot_player_2->v_x = pressed_left*(-SLIME_V_X) + pressed_right*SLIME_V_X;
	if (pressed_up && cmot_player_2->v_y == 0) {
		cmot_player_2->v_y = SLIME_V_Y;
	}

	cmot_player_1->v_x = pressed_a*(-SLIME_V_X) + pressed_d*SLIME_V_X;
	if (pressed_w && cmot_player_1->v_y == 0) {
		cmot_player_1->v_y = SLIME_V_Y;
	}

	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_P, false))
	{
		// TODO: exit pauzed state when pressed P again
		engine->GetContext()->SetPaused(true);
		/*
		if (!engine->GetContext()->IsPaused()) {
		engine->GetContext()->SetPaused(true);
		}
		else {
		engine->GetContext()->SetPaused(false);
		}
		*/
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_ESCAPE, false))
	{
		// Quit without saving
		engine->GetContext()->SetState(4);
		engine->GetContext()->ToggleKey(ALLEGRO_KEY_ESCAPE, false);
	}
}

bool SystemInputMulti::Initialize()
{
	// Initialize all component pointers (optional)
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1)
		{
			cmot_player_1 = (ComponentMotion*)i->GetComponent(Component::MOTION);
		}
		else if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 2)
		{
			cmot_player_2 = (ComponentMotion*)i->GetComponent(Component::MOTION);
		}
	}

	return true;
}
