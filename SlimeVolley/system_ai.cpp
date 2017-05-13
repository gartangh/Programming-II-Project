#include "system_ai.h"

#include <set>
#include <iostream>
#include <cmath>

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

SystemAI::Prediction SystemAI::XBallBelow(double y_target, double co_x_ball, double co_y_ball, double v_x_ball, double v_y_ball, double a_y_ball)
{
	// TODO: Calculate the value of x when y is first below y_target
	//Calculate time to hit y value
	//Py  = Pn + v*t +(a/2)*t^2
	//t1 = (-v+sqrt(-2*Pn*a +2*Py*a+v^2))/a

	int Pn = cspr_ball->y;
	int v = cmot_ball->v_y;
	double a = cmot_ball->a_y;

	double wortel = sqrt(-2 * co_y_ball*a_y_ball + 2 * y_target*a_y_ball + v_y_ball*v_y_ball);
	double t1 = (-v_y_ball + wortel) / a_y_ball;
	double t2 = (-v_y_ball - wortel) / a_y_ball;
	
	if (t1 < 0) {
		SystemAI::Prediction a = { co_x_ball + t2*v_x_ball, v_x_ball, v_y_ball + t2*a_y_ball, cmot_ball->v_x == v_x_ball };
		return a;
	}
	else {
		SystemAI::Prediction a = { co_x_ball + t1*v_x_ball, v_x_ball, v_y_ball + t1*a_y_ball, cmot_ball->v_x == v_x_ball };
		return a;
	}

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
	Stop();
	//int co_test = CheckBellowWithWall(cspr_ball->x, cspr_ball->y, cmot_ball->v_x, cmot_ball->v_y, cmot_ball->a_y);
	
	if (level == 3)
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
		SystemAI::Prediction pred = XBallBelow(90, cspr_ball->x, cspr_ball->y, cmot_ball->v_x, cmot_ball->v_y, cmot_ball->a_y);
		double P = pred.co_x;

		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 600 (i.e. use abs(x - 600) < 6) by moving left/right (otherwise just stop)
		//    Return
		if (P <= MIDDLE) {
			if (abs(cspr_player_2->x - 600) > 6) {
				if (cspr_player_2->x < 600) {
					MoveRight();
				}
				else {
					MoveLeft();
				}
			}
			else {
				Stop();
			}

			return;
		}

		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150
		//        Jump
		//    Return
		if (abs(P - cspr_player_2->x) < 25 && cspr_player_2->y == 0) {
			if (cspr_player_2->x >= 675 && cspr_ball->x > 625)
				Jump();
			if (cspr_player_2->x <= 435 && cspr_ball->x < 395 && abs(cspr_ball->x - cspr_player_2->x) < 75)
				Jump();
			if (abs(cspr_ball->x - cspr_player_2->x) < 110 && cspr_ball->y > 25 && cspr_ball->y < 150)
				Jump();

			return;
		}

		// Else if the slime is on the ground
		//    Position it as close as possible to P (use abs limit 25 instead of 6)
		else if (cspr_player_2->y == 0) {
			if (abs(P - cspr_player_2->x) > 25) {
				if (P > cspr_player_2->x) {
					MoveRight();
				}
				else {
					MoveLeft();
				}
			}
		}

		// Else if the slime's x >= 675
		//    Move right
		else if (cspr_player_2->x >= 675) {
			MoveRight();
		}

		// Else
		//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
		else {
			if (abs(cspr_ball->x - cspr_player_2->x) >= 25) {
				if (cspr_ball->x > cspr_player_2->x) {
					MoveRight();
				}
				else {
					MoveLeft();
				}
			}
		}
	}

	else if (level == 2)
	{
		// If ball is on left side of the net, set state equal to -1
		if (cspr_ball->x < MIDDLE)
		{
			state = -1;
		}

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
		if (state != -1 || (cmot_ball->v_x == 0 && cspr_ball->x == 600)) {
			if (state == -1) {
				state = rand() % 3;
			}
			if (state == 0) {
				if (cspr_ball->y < 75) {
					MoveRight();
					Jump();
				}
			}
			if (state == 1) {
				if (cspr_ball->y < 75) {
					MoveLeft();
					Jump();
				}
			}
			if (state == 2) {
					//		If the ball's vertical speed is higher than 4.5 and slime's x < 645
					//          Move right (until slime's x >= 645)
					//      If slime's x >= 645
					//          Stop
					//      If the ball's vertical speed equals -1.125 and slime's x != 600
					//          Jump
					//      If the ball's vertical speeds is lower than -4.5 and the slime is mid-air and slime's x >= 633
					//          Move left

				if (cmot_ball->v_y > 4.5 && cspr_player_2->x < 645) {
					MoveRight();
				}
				if (cspr_player_2->x >= 645) {
					Stop();
				}
				if (cmot_ball->v_y == -1.125 && cspr_player_2->x != 600) {
					Jump();
				}
				if (cmot_ball->v_y < -4.5 && cspr_player_2->y > 0 && cspr_player_2->x >= 633) {
					MoveLeft();
				}
			}

			return;
		}

		// Calculate the x-value of the first position at which the ball drops below y = 90 (call this position P)
		SystemAI::Prediction pred = XBallBelow(90, cspr_ball->x, cspr_ball->y, cmot_ball->v_x, cmot_ball->v_y, cmot_ball->a_y);
		double P = pred.co_x;

		// If P is on the left side of the net
		//    Position the slime closer than distance 6 to x = 480 (i.e. use abs(x - 480) < 6) by moving left/right (otherwise just stop)
		//    Return
		if (P <= MIDDLE) {
			if (abs(cspr_player_2->x - 480) > 6) {
				if (cspr_player_2->x < 480) {
					MoveRight();
				}
				else {
					MoveLeft();
				}
			}
			else {
				Stop();
			}

			return;
		}

		// If the horizontal distance between P and the slime is less than 25, and the slime is on the ground
		//    If Slime's x >= 675 and ball's x > 625
		//        Jump
		//    If Slime's x <= 435 and ball's x < 395 and horizontal distance between ball and slime is less than 75
		//        Jump
		//    If Horizontal distance between ball and slime is less than 110 and ball's y > 25 and ball's y < 150 and random value < 0.5
		//        Jump
		//    Return
		if (abs(P - cspr_player_2->x) < 25 && cspr_player_2->y == 0) {
			if (cspr_player_2->x >= 675 && cspr_ball->x > 625)
				Jump();
			if (cspr_player_2->x <= 435 && cspr_ball->x < 395 && abs(cspr_ball->x - cspr_player_2->x) < 75)
				Jump();
			if (abs(cspr_ball->x - cspr_player_2->x) < 110 && cspr_ball->y > 25 && cspr_ball->y < 150 && (double)rand()/(RAND_MAX) < 0.5)
				Jump();

			return;
		}

		// Else if the slime is on the ground
		//    Position it as close as possible to P (use abs limit 25 instead of 6)
		else if (cspr_player_2->y == 0) {
			if (abs(P - cspr_player_2->x) > 25) {
				if (P > cspr_player_2->x) {
					MoveRight();
				}
				else {
					MoveLeft();
				}
			}
		}

		// Else if the slime's x >= 675
		//    Move right
		else if (cspr_player_2->x >= 675) {
			MoveRight();
		}

		// Else
		//     Position the slime as close as possible to the ball (use abs limit 25 instead of 6)
		else {
			if (abs(cspr_ball->x - cspr_player_2->x) >= 25) {
				if (cspr_ball->x > cspr_player_2->x) {
					MoveRight();
				}
				else {
					MoveLeft();
				}
			}
		}
	}

	else if (level == 1)
	{
		//Goal bounce ball against wall and in net
		
			//Ball heading to AI
		
		std::cout << "=====================\n";
		
		
		


		SystemAI::Prediction pred = CheckBellowWithWall(cspr_ball->x, cspr_ball->y, cmot_ball->v_x, cmot_ball->v_y, cmot_ball->a_y);
		double est = pred.co_x;
		std::cout << "Estimate: " << est << "\n";
		std::cout << "=====================\n";

		//opzet
		if (cmot_ball->v_x == 0 && cspr_ball->x > MIDDLE) {
			
			if (cspr_player_2->x - cspr_ball->x < 32) {
				MoveLeft();
			}
			if (cspr_ball->y < 40) {
				Jump();
			}
		}

		//if(cmot_ball->v_x > 0 || )
		int loc;
		if (est >= MIDDLE) {
			if (pred.v_x > 0 || cspr_player_2->x < 750 - RADIUS_SLIME +5) {
				//GO to left of ball
				loc = est + 15;
			}
			else {
				loc = est - 15;
			}
			double dist = loc - cspr_player_2->x;
			std::cout << "dist: " << dist << std::endl;
			if (dist < 0) {
				std::cout << "move Left" << std::endl;
				if(cspr_player_2->x > MIDDLE + RADIUS_SLIME && abs(dist) > 3)
					MoveLeft();
			}
			else {
				std::cout << "move Right" << std::endl;
				if (cspr_player_2->x < GAME_WIDTH - RADIUS_SLIME && abs(dist) > 3)
					MoveRight();
			}
			if ((cspr_ball->x - cspr_player_2->x)*(cspr_ball->x - cspr_player_2->x) + (cspr_ball->y - cspr_player_2->y)*(cspr_ball->y - cspr_player_2->y) < (RADIUS_COLLISION + 10)*(RADIUS_COLLISION + 10)) {
				Jump();
			}
		}
		else {
			//Move to middle of field
			int loc = GAME_WIDTH*(3.0 / 4.0) - cspr_player_2->x;
			if (loc < 0) {
				if (cspr_player_2->x > MIDDLE + RADIUS_SLIME && abs(loc) > 3)
					MoveLeft();
			}
			else {
				if (cspr_player_2->x < GAME_WIDTH - RADIUS_SLIME && abs(loc) > 3)
					MoveRight();
			}
		}
		
		
	}
}
SystemAI::Prediction SystemAI::CheckBellowWithWall(double co_x_ball, double co_y_ball, double v_x_ball, double v_y_ball, double a_y_ball)
{
	//TODO for left wall
	double time;
	int loc;
	if (v_x_ball > 0) {
		 time = (750.0 - co_x_ball - RADIUS_BALL) / v_x_ball;
		 loc = 750-RADIUS_BALL;
	}
	else if (v_x_ball < 0){
		time = (co_x_ball-RADIUS_BALL) / ((-1)*v_x_ball);
		loc = RADIUS_BALL;
	}
	else {
		SystemAI::Prediction a = { co_x_ball, 0,-5 ,false };
		return a;
	}

	double pred_y_ball = co_y_ball + time*v_y_ball + (time*time*a_y_ball)/2;

	std::cout << "estimated time: " << time << "\n";
	std::cout << "estimated height: " << pred_y_ball << "\n";
	if (pred_y_ball > 0) {
		return CheckBellowWithWall(loc, pred_y_ball, (-1)*v_x_ball, v_y_ball + time*a_y_ball, a_y_ball);
	}
	else {
		return XBallBelow(RADIUS_BALL + 15,  co_x_ball,  co_y_ball,  v_x_ball,  v_y_ball,  a_y_ball);
	}
}
void SystemAI::UpdateMovement()
{
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
