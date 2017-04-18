#include "system_ai.h"

#include <set>
#include <iostream>

#include "component.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_sprite.h"
#include "entity.h"
#include "engine.h"

void SystemAI::Update()
{
	// Initialize (optional)
	if (!initialized)
	{
		initialized = Initialize();
	}

	// Reset state and AI's decisions
	if (engine->GetContext()->GetState() != 0)
	{
		state = -1;
		Stop();
	}

	// Update AI's decisions if the game is not paused
	if (!engine->GetContext()->IsPaused())
	{
		UpdateKeys();
	}

	// Update player's movement
	UpdateMovement();
}

double SystemAI::XBallBelow(double y_target)
{
	// TODO: Calculate the value of x when y is first below y_target
	//Calculate time to hit y value
	//Py  = Pn + v*t +(a/2)*t^2
	//t1 = (-v+sqrt(-2*Pn*a +2*Py*a+v^2))/a

	int Pn = cspr_ball->y;
	int v = cmot_ball->v_y;
	double a = cmot_ball->a_y;

	double wortel = sqrt(-2 * Pn*a + 2 * y_target*a + v*v);
	double t1 = (-v + wortel) / a;
	double t2 = (-v - wortel) / a;
	
	if (t1 < 0) {
		return cspr_ball->x + t2*cmot_ball->v_x;
	}
	else {
		return cspr_ball->x + t1*cmot_ball->v_x;
	}

	return 0;
}

void SystemAI::MoveLeft()
{
	pressed_left = true;
	pressed_right = false;
}

void SystemAI::MoveRight()
{
	pressed_left = false;
	pressed_right = true;
}

void SystemAI::Jump()
{
	pressed_up = true;
}

void SystemAI::Stop()
{
	pressed_left = false;
	pressed_right = false;
	pressed_up = false;
}

float SystemAI::GetRandom()
{
	return (float)rand() / (RAND_MAX);
}

void SystemAI::UpdateKeys()
{
	int level = engine->GetContext()->GetLevel();

	if (level == 1)
	{
		// If ball is on left side of the net, set state equal to -1
		if (cspr_ball->x < MIDDLE)
		{
			state = -1;
		}
		
		// If state equals 0 or the ball is in serving position (v_x == 0, x == 600)
		//    Set state equal to 0 and serve only if the ball drops below y = 110 by simply moving right and jump
		//    Return
		if (state = 0 || (cmot_ball->v_x == 0 && cspr_ball->x == 600))
		{
			state = 0;
			if (cspr_ball->y < 110) {
				MoveRight();
				Jump();

				return;
			}
		}
		
		// Calculate the x-value of the first position at which the ball drops below y = 90 (call this position P)
		double P = XBallBelow(90);
		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 600 (i.e. use abs(x - 600) < 6) by moving left/right (otherwise just stop)
		//    Return
		if (P < MIDDLE) {
			if (cspr_player_2->x < 594) {
				MoveRight();
			}
			else if (cspr_player_2->x > 606) {
				MoveLeft();
			}
		}

		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150
		//        Jump
		//    Return
		if (abs(P - cspr_ball->x) < 25 && cspr_player_2->y == 0) {
			if (cspr_player_2->x >= 625 && cspr_ball->x > 625)
				Jump();
			if (cspr_player_2->x <= 435 && cspr_ball->x < 395 && abs(cspr_ball->x - cspr_player_2->x) < 75)
				Jump();
			if (abs(cspr_ball->x - cspr_player_2->x) < 110 && cspr_ball->y > 25 && cspr_ball->y < 150)
				Jump();
			return;
		}
		Stop();

		// Else if the slime is on the ground
		//    Position it as close as possible to P (use abs limit 25 instead of 6)

		// Else if the slime's x >= 675
		//    Move right

		// Else
		//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
	}
	else if (level == 2)
	{
		// If ball is on left side of the net, set state equal to -1

		// If state does not equal -1 or the ball is in serving position (v_x = 0, x == 600)
		//    If state equals -1
		//        Randomly set the state equal to 0, 1 or 2
		//    If state equals 0
		//        If the ball drops below y = 75, move right and jump
		//    If state equals 1
		//        If the ball drops below y = 75, move left and jump
		//    If state equals 2
		//        If the ball's vertical speed is higher than 4.5 and slime's x < 645
		//            Move right (until slime's x >= 645)
		//        If slime's x >= 645
		//            Stop
		//        If the ball's vertical speed equals -1.125 and slime's x != 600
		//            Jump
		//        If the ball's vertical speeds is lower than -4.5 and the slime is mid-air and slime's x >= 633
		//            Move left
		//    Return

		// Calculate the x-value of the first position at which the ball drops below y = 90 (call this position P)

		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 480 (i.e. use abs(x - 480) < 6) by moving left/right (otherwise just stop)
		//    Return

		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150 and random value < 0.5
		//        Jump
		//    Return

		// Else if the slime is on the ground
		//    Position it as close as possible to P (use abs limit 25 instead of 6)

		// Else if the slime's x >= 675
		//    Move right

		// Else
		//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
	}
	else if (level == 3)
	{
		// OPTIONEEL ZELF TE IMPLEMENTEREN!
	}
}

void SystemAI::UpdateMovement()
{
	// TODO: Change player's movement according to AI decisions (i.e. pressed_xxx)
	cmot_player_2->v_x = pressed_left*(-SLIME_V_X) + pressed_right*SLIME_V_X;
	if (pressed_up && cmot_player_2->v_y == 0) {
		cmot_player_2->v_y = SLIME_V_Y;
	}
}

bool SystemAI::Initialize()
{
	// Initialize all component pointers (optional)
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::PLAYER);
	for each (Entity* i in entities)
	{
		if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 1)
		{
			cspr_player_1 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
		}
		else if (((ComponentPlayer*)i->GetComponent(Component::PLAYER))->player_id == 2)
		{
			cspr_player_2 = (ComponentSprite*)i->GetComponent(Component::SPRITE);
			cmot_player_2 = (ComponentMotion*)i->GetComponent(Component::MOTION);
		}
	}

	entities = engine->GetEntityStream()->WithTag(Component::BALL);
	for each (Entity* i in entities)
	{
		cspr_ball = (ComponentSprite*)i->GetComponent(Component::SPRITE);
		cmot_ball = (ComponentMotion*)i->GetComponent(Component::MOTION);
	}

	return true;
}
