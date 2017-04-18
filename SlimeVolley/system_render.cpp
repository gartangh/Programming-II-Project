#include "system_render.h"

#include <chrono>
#include <iostream>
#include <set>
#include <thread>
#include <vector>

#include "color.h"
#include "component.h"
#include "component_player.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "graphics.h"
#include "tags.h"

void SystemRender::Update()
{
	// Initialize (required)
	if (!initialized)
	{
		initialized = Initialize();
	}

	//cout << "Rendering...";

	// Clear screen and draw background
	Graphics::Instance().ClearScreen();
	Graphics::Instance().DrawBackground();

	// Iterate over all entities with the sprite component and print to
	// screen. For player slimes, draw the pupils as well.

	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::SPRITE);
	std::vector<ComponentSprite*> pupils;
	for (set<Entity*>::iterator i = entities.begin(); i != entities.end(); i++) {
		ComponentSprite *sprite_comp = (ComponentSprite*)(*i)->GetComponent(Component::SPRITE);
		if (sprite_comp->sprite == Graphics::SPRITE_PUPIL) {
			pupils.push_back(sprite_comp);
		}
		else {
			Graphics::Instance().DrawBitmap(sprite_comp->sprite, sprite_comp->x, COY(sprite_comp->y), sprite_comp->x_off, sprite_comp->y_off);
		}
	}

	int a = 0;
	set<Entity*> players = engine->GetEntityStream()->WithTag(Component::PLAYER);

	for (set<Entity*>::iterator i = players.begin(); i != players.end(); i++) {
		ComponentPlayer *play_comp = (ComponentPlayer*)(*i)->GetComponent(Component::PLAYER);
		Graphics::Instance().DrawBitmap(pupils.at(a)->sprite, play_comp->pupil_x, COY(play_comp->pupil_y), pupils.at(a)->x_off, pupils.at(a)->y_off);
		a++;
	}
	

	// Use an appropriate color for the different backgrounds
	Color color(0, 0, 0); // Black
	if (engine->GetContext()->GetLevel() == 2) {
		color = Color(255, 255, 255); // White
	}

	// TODO: Print the current score if it is a singleplayer game
	if (engine->GetContext()->GetLevel() > 0)
	{
		Graphics::Instance().DrawString("Score: ", 375, 0, color, Graphics::ALIGN_CENTER);
	}
	
	// TODO: Print the correct instructions at the bottom of the screen,
	// depending on whether there's a regular game or a replay
	if (engine->GetContext()->IsReplay())
	{
		Graphics::Instance().DrawString("Speed down (LEFT), up (Right) or up (P)", 20, 310, color, Graphics::ALIGN_LEFT);
		Graphics::Instance().DrawString("Next point (UP), Level (DOWN) or quit (ESC)", 20, 342, color, Graphics::ALIGN_LEFT);
	}
	else
	{
		Graphics::Instance().DrawString("Press P to pauze of ESC to quit without saving", 375, 342, color, Graphics::ALIGN_CENTER);
	}
	
	// TODO: Print an appropriate message if state != 0, depending on state
	// and current level (1-3 for singleplayer, 0 for multiplayer)
	switch (engine->GetContext()->GetState())
	{
	case -1:
		switch (engine->GetContext()->GetLevel()) {
		case 2:
			Graphics::Instance().DrawString("The slime Intermediate can go to cry in a corner!", 375, 75, color, Graphics::ALIGN_CENTER);
			break;
		case 3:
			Graphics::Instance().DrawString("The slime Expert clearly was no match for you!", 375, 75, color, Graphics::ALIGN_CENTER);
			break;
		default:
			Graphics::Instance().DrawString("The slime Novice needs more practice to beat you!", 375, 75, color, Graphics::ALIGN_CENTER);
		}
		Graphics::Instance().DrawString("Press space to continue or esc to quit without saving", 375, 100, color, Graphics::ALIGN_CENTER);
		break;
	case -2:
		Graphics::Instance().DrawString("Winners never quit, and quiters nevver win...", 375, 75, color, Graphics::ALIGN_CENTER);
		Graphics::Instance().DrawString("Press space to retry or esc to quit", 375, 100, color, Graphics::ALIGN_CENTER);
		break;
	case -3:
		Graphics::Instance().DrawString("Player 1 wins!", 375, 75, color, Graphics::ALIGN_CENTER);
		break;
	case -4:
		Graphics::Instance().DrawString("Player 2 wins!", 375, 75, color, Graphics::ALIGN_CENTER);
		break;
	case -5:
		if (engine->GetContext()->GetLevel() == 0)
		{
			Graphics::Instance().DrawString("Nice touch, Player 1!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		else
		{
			Graphics::Instance().DrawString("Nice touch!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		break;
	case -6:
		if (engine->GetContext()->GetLevel() == 0)
		{
			Graphics::Instance().DrawString("Player 1 does it again!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		else
		{
			Graphics::Instance().DrawString("GO GO GO!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		break;
	case -7:
		if (engine->GetContext()->GetLevel() == 0)
		{
			Graphics::Instance().DrawString("You go, Player 1!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		else
		{
			Graphics::Instance().DrawString("You're going places!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		break;
	case -8:
		if (engine->GetContext()->GetLevel() == 0)
		{
			Graphics::Instance().DrawString("Nice touch, Player 2!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		else
		{
			Graphics::Instance().DrawString("Did you lose some focus? Come on!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		break;
	case -9:
		if (engine->GetContext()->GetLevel() == 0)
		{
			Graphics::Instance().DrawString("Player 2 does it again!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		else
		{
			Graphics::Instance().DrawString("Are you asleep? Wake up!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		break;
	case -10:
		if (engine->GetContext()->GetLevel() == 0)
		{
			Graphics::Instance().DrawString("You go, Player 2!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		else
		{
			Graphics::Instance().DrawString("Come on, you can do better!", 375, 310, color, Graphics::ALIGN_CENTER);
		}
		break;
	}

	// Update current frame rate
	fps_accum++;
	t = al_get_time();
	if (t - fps_time >= 1)
	{
		fps = fps_accum;
		fps_accum = 0;
		fps_time = t;
	}
	Graphics::Instance().DrawString(std::to_string(fps), 375, 40, color, Graphics::ALIGN_CENTER);

	// Execute all draws
	Graphics::Instance().ExecuteDraws();
}

bool SystemRender::Initialize()
{
	// TODO: Set background according to level
	//engine->GetContext()->GetLevel();

	return true;
}
