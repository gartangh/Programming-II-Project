#pragma once

#include "component_sprite.h"
#include "component_player.h"
#include "system.h"

class SystemEyes : public System
{
public:
	SystemEyes() : System(), initialized(false)
	{
		
	};

	virtual ~SystemEyes()
	{
	};

	virtual void Update();

protected:
	virtual Type GetType()
	{
		return System::TYPE_EYES;
	};

private:
	bool Initialize();

	bool initialized;
	ComponentSprite* cspr_player_1;
	ComponentPlayer* cpla_player_1;
	ComponentSprite* cspr_player_2;
	ComponentPlayer* cpla_player_2;
	ComponentSprite* cspr_ball;
};
