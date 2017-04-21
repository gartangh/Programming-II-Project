#include "game_replay.h"

#include "allegro_lib.h"
#include "component_ball.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_point.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "entity_stream.h"
#include "graphics.h"

GameReplay::GameReplay(Context* _context, int _level, std::string _input_file) :
	context(_context),
	level(_level),
	inputFile(_input_file),
	engine(_context)
{
	AddSystems();
	MakeEntities();
	context->SetLevel(level);
};

GameReplay::~GameReplay()
{
	RemoveSystems();
	DestroyEntities();
}

bool GameReplay::Run()
{
	// Set replay mode and input file in context
	context->SetReplay(true);
	context->SetInputFile(inputFile);

	// Initialize game loop
	AllegroLib::Instance().StartLoop();
	bool quit = AllegroLib::Instance().IsWindowClosed();

	// Enter game loop
	while (!quit && context->GetState() <= 0)
	{
		// Start Allegro iteration
		AllegroLib::Instance().StartIteration();

		// Get the current Allegro event
		ALLEGRO_EVENT event = AllegroLib::Instance().GetCurrentEvent();

		// If event key down, toggle key in context
		// TODO: change Z, Q & D to UP, LEFT & RIGHT
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			int keycode = event.keyboard.keycode;
			if (keycode == ALLEGRO_KEY_UP || keycode == ALLEGRO_KEY_LEFT || keycode == ALLEGRO_KEY_RIGHT ||
				keycode == ALLEGRO_KEY_P || keycode == ALLEGRO_KEY_ESCAPE || keycode == ALLEGRO_KEY_SPACE)
			{
				context->ToggleKey(keycode, true);
			}
		}
		// If event key up, untoggle key in context
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			int keycode = event.keyboard.keycode;
			if (keycode == ALLEGRO_KEY_UP || keycode == ALLEGRO_KEY_LEFT || keycode == ALLEGRO_KEY_RIGHT ||
				keycode == ALLEGRO_KEY_P || keycode == ALLEGRO_KEY_ESCAPE || keycode == ALLEGRO_KEY_SPACE)
			{
				context->ToggleKey(keycode, false);
			}
		}
		// If event timer, update engine
		else if (event.type == ALLEGRO_EVENT_TIMER)
		{
			engine.Update();
		}

		// The following six lines clear the screen, redraw the background,
		// draw sprites and render both to screen. This should be handled by
		// the render system, but is here to make sure Allegro works properly.
		Graphics::Instance().ClearScreen();
		Graphics::Instance().DrawBackground();
		Graphics::Instance().DrawBitmap(Graphics::SPRITE_PLAYER1, 150, 299 - 0, 39, 39);
		Graphics::Instance().DrawBitmap(Graphics::SPRITE_PLAYER2, 600, 299 - 0, 39, 39);
		Graphics::Instance().DrawBitmap(Graphics::SPRITE_BALL, 150, 299 - 133.5, 11, 11);
		Graphics::Instance().ExecuteDraws();

		// Update quit value
		quit = AllegroLib::Instance().IsWindowClosed();
	}

	// Reset replay mode in context
	context->SetReplay(false);

	// Reset game state in context and return
	bool state = context->GetState() == 1;
	context->SetState(0);
	return state;
}

void GameReplay::AddSystems()
{
	// TODO: Add all systems to the engine

}

void GameReplay::RemoveSystems()
{
	// TODO: Remove all systems from the engine

}

void GameReplay::MakeEntities()
{
	// TODO: Initialize required entities and add them to the engine

}

void GameReplay::DestroyEntities()
{
	// TODO: Remove and destroy all entities

}
