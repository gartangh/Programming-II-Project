#include "system_state_single.h"

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

void SystemStateSingle::Update()
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

				if (cspr_ball->x >= MIDDLE)
				{
					winner = 1;
					engine->GetContext()->SetState(rand() % 3 - 7);
					engine->GetContext()->IncreasePoints(1);
				}
				else
				{
					winner = 2;
					engine->GetContext()->SetState(rand() % 3 - 10);
					engine->GetContext()->IncreasePoints(2);
				}
			}
		}
		else
		{
			// TODO: Decrease freeze time by one. If it becomes zero and one
			// of the players scored seven points, update the context as to
			// end the level gracefully. Wait for user input: spacebar to
			// continue to next level (if won) or retry (if lost), ESC to quit
			// (handled by input system already). If the game is not finished
			// yet, update the context and reset player and ball positions.
			freeze_time--;

			if (freeze_time == 0)
			{
				if (engine->GetContext()->GetPoints(1) == 7)
				{
					engine->GetContext()->SetState(-1); // De speler heeft een level gewonnen in een singleplayer game
				}
				else if (engine->GetContext()->GetPoints(2) == 7)
				{
					engine->GetContext()->SetState(-2); // De speler heeft een level verloren in een singleplayer game
				}
				else
				{
					// Verliezer slaat op
					if (winner == 2)
					{
						cspr_ball->x = SLIME_1_INIT_X;
					}
					else
					{
						cspr_ball->x = SLIME_2_INIT_X;
					}
					cspr_ball->y = BALL_INIT_Y;
					cspr_player_1->x = SLIME_1_INIT_X;
					cspr_player_1->y = GROUND;
					cspr_player_2->x = SLIME_2_INIT_X;
					cspr_player_2->y = GROUND;

					engine->GetContext()->SetState(0); // De bal is in het spel
					engine->GetContext()->SetFrozen(false);
				}
			}
		}
	}
}

bool SystemStateSingle::Initialize()
{
	// TODO: Initialize all component pointers (optional)
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::BALL);
	for each (Entity* i in entities)
	{
		cspr_ball = (ComponentSprite*)i->GetComponent(Component::SPRITE);
		cmot_ball = (ComponentMotion*)i->GetComponent(Component::MOTION);
	}

	entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1) {
			cspr_player_1 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
			cmot_player_1 = (ComponentMotion*)i->GetComponent(Component::MOTION);
		}
		else if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 2) {
			cspr_player_2 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
			cmot_player_2 = (ComponentMotion*)i->GetComponent(Component::MOTION);
		}
	}

	return true;
}

void SystemStateSingle::setBall(ComponentSprite *cspr_ball) {
	this->cspr_ball = cspr_ball;
}
