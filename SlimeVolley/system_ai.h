#pragma once

#include <time.h>

#include "component_motion.h"
#include "component_sprite.h"
#include "system.h"

class SystemAI : public System
{
public:
	SystemAI() : System(), initialized(false), state(-1), pressed_left(false), pressed_right(false), pressed_up(false)
	{
		srand((unsigned int)time(NULL));
	};

	~SystemAI()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_AI;
	};

private:

	struct Prediction
	{
		double co_x;
		double v_x;
		double v_y;
		bool hitwall;
	};

	bool Initialize();
	void UpdateKeys();
	void UpdateMovement();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Stop();
	float GetRandom();
	Prediction XBallBelow(double y_target, double co_x_ball, double co_y_ball, double v_x_ball, double v_y_ball, double a_y_ball);
	Prediction CheckBellowWithWall(double co_x_ball, double co_y_ball, double v_x_ball, double v_y_ball, double a_y_ball);

	bool initialized;
	int state;
	bool pressed_left;
	bool pressed_right;
	bool pressed_up;
	ComponentSprite* cspr_player_1;
	ComponentSprite* cspr_player_2;
	ComponentMotion* cmot_player_2;
	ComponentSprite* cspr_ball;
	ComponentMotion* cmot_ball;
	
};
