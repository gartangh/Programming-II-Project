#include "system_state_multi.h"

#include <set>

#include "component.h"
#include "component_player.h"
#include "component_motion.h"
#include "component_sprite.h"
#include "context.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "tags.h"

void SystemStateMulti::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Is the game running?
	if (!engine->GetContext()->IsPaused())
	{
		// Is the level in freeze state?
		if (freeze_time == 0)
		{
			// TODO: Check if the ball has dropped. If so, freeze the game for
			// 1.2 seconds and reset all velocities. Determine the winner and
			// update the context accordingly.
			if (cspr_ball->y <= 0) {
				engine->GetContext()->SetFrozen(true);
				freeze_time = 48; // 1.2 seconds
				
				cmot_ball->v_x = 0;
				cmot_ball->v_y = 0;
				cmot_player_1->v_x = 0;
				cmot_player_1->v_y = 0;
				cmot_player_2->v_x = 0;
				cmot_player_2->v_y = 0;

				if (cspr_ball->x <= MIDDLE) {
					winner = 1;
					engine->GetContext()->SetState(rand() % 3 - 7);
					engine->GetContext()->IncreasePoints(1);
				}
				else {
					winner = 2;
					engine->GetContext()->SetState(rand() % 3 - 10);
					engine->GetContext()->IncreasePoints(2);
				}
			}
		}
		else
		{
			// TODO: Decrease freeze time by one. If it becomes zero and one
			// of the players scored seven points, update the context and wait
			// for	user input: spacebar to restart, ESC to quit (handled by
			// input system already). If the game is not finished yet, update
			// the context and reset player and ball positions.
			freeze_time--;
			if (freeze_time == 0) {
				if (this->)
			}
		}
	}
}

bool SystemStateMulti::Initialize()
{
	// TODO: Initialize all component pointers (optional)

	return true;
}
