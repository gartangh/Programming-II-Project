#include "system_input_single.h"

#include "allegro_lib.h"
#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "engine.h"

void SystemInputSingle::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		Initialize();
	}

	// TODO: Change player's movement, pause and exit according to toggled
	// keys in context
	pressed_left = engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_LEFT, false);
	pressed_right = engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_RIGHT, false);
	pressed_up = engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_UP, false);

	cmot_player_1->v_x = pressed_left*(-SLIME_V_X) + pressed_right*SLIME_V_X;
	if (pressed_up && cmot_player_1->v_y == 0) {
		cmot_player_1->v_y = SLIME_V_Y;
	}

	if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_P, false))
	{
		engine->GetContext()->SetPaused(true);
	}
	else if (engine->GetContext()->GetKeyPressed(ALLEGRO_KEY_ESCAPE, false))
	{
		// TODO: quit without saving
	}
}

bool SystemInputSingle::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1)
		{
			cmot_player_1 = (ComponentMotion*)i->GetComponent(Component::MOTION);
		}
	}

	return true;
}
