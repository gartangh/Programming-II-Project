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
	Color c(0, 0, 0); // Black
	if (engine->GetContext()->GetLevel() == 2) {
		c = Color(255, 255, 255); // White
	}

	
	// TODO: Print the current score if it is a singleplayer game
	/*
	if () {
		Graphics::Instance().DrawString("Score: ", 375, 0, c, Graphics::ALIGN_CENTER);
		Graphics::Instance().ExecuteDraws();
	}
	*/
	// TODO: Print the correct instructions at the bottom of the screen,
	// depending on whether there's a regular game or a replay
	int state = engine->GetContext()->GetState();
	

	// TODO: Print an appropriate message if state != 0, depending on state
	// and current level (1-3 for singleplayer, 0 for multiplayer)

	// Update current frame rate
	fps_accum++;
	t = al_get_time();
	if (t - fps_time >= 1)
	{
		fps = fps_accum;
		fps_accum = 0;
		fps_time = t;
	}
	Graphics::Instance().DrawString(std::to_string(fps), 375, 40, c, Graphics::ALIGN_CENTER);

	// Execute all draws
	Graphics::Instance().ExecuteDraws();
}

bool SystemRender::Initialize()
{
	int level = engine->GetContext()->GetLevel();

	// TODO: Set background according to level

	return true;
}
