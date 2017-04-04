#include "game_single.h"

#include "allegro_lib.h"
#include "component_ball.h"
#include "component_motion.h"
#include "component_player.h"
#include "component_point.h"
#include "component_sprite.h"
#include "entity.h"
#include "entity_stream.h"
#include "graphics.h"
#include <iostream>

#define QKEY 17
#define ZKEY 26
#define SKEY 19
#define DKEY 4

#define UPKEY 84
#define DOWNKEY 85
#define LEFTKEY 82
#define RIGHTKEY 83


GameSingle::GameSingle(Context* _context, int _level) :
	context(_context),
	engine(_context),
	level(_level)
{
	AddSystems();
	MakeEntities();
	context->SetLevel(level);
};

GameSingle::~GameSingle()
{
	RemoveSystems();
	DestroyEntities();
}

int GameSingle::Run()
{
	// Initialize game loop
	AllegroLib::Instance().StartLoop();
	bool quit = AllegroLib::Instance().IsWindowClosed();

	// Enter game loop
	while (!quit && context->GetState() <= 0)
	{
		// Start Allegro iteration
		AllegroLib::Instance().StartIteration();

		//Detects KEY_UP, KEY_DOWN and TIMER and updates context
		ALLEGRO_EVENT event = AllegroLib::Instance().GetCurrentEvent();
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == QKEY || event.keyboard.keycode == ZKEY ||
				event.keyboard.keycode == SKEY || event.keyboard.keycode == DKEY ||
				event.keyboard.keycode == UPKEY || event.keyboard.keycode == DOWNKEY ||
				event.keyboard.keycode == LEFTKEY || event.keyboard.keycode == RIGHTKEY) {
				context->ToggleKey(event.keyboard.keycode, true);
			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			if (event.keyboard.keycode == QKEY || event.keyboard.keycode == ZKEY ||
				event.keyboard.keycode == SKEY || event.keyboard.keycode == DKEY ||
				event.keyboard.keycode == UPKEY || event.keyboard.keycode == DOWNKEY ||
				event.keyboard.keycode == LEFTKEY || event.keyboard.keycode == RIGHTKEY) {
				context->ToggleKey(event.keyboard.keycode, false);
			}
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			engine.Update();
		}
		// TODO: If event key down, toggle key in context

		// TODO: If event key up, untoggle key in context

		// TODO: If event timer, update engine

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

	// Reset game state in context and return
	int state = context->GetState();
	context->SetState(0);
	return state;
}

void GameSingle::AddSystems()
{
	// TODO: Add all systems to the engine

}

void GameSingle::RemoveSystems()
{
	// TODO: Remove all systems from the engine

}

void GameSingle::MakeEntities()
{
	// TODO: Initialize required entities and add them to the engine
	Entity *ball = new Entity();
	ball->Add(new ComponentSprite(Graphics::SPRITE_BALL, 150, 11, 738, -11, 150, 11, 288, 11));
	ball->Add(new ComponentMotion(0, 0, 0, -1));
	ball->Add(new ComponentBall());
	engine.AddEntity(ball);

	Entity *player1 = new Entity(); //double _x, double _x_min, double _x_max, double _x_off, double _y, double _y_min, double _y_max, double _y_off)
	player1->Add(new ComponentSprite(Graphics::SPRITE_PLAYER1, 150, 39, 738, -39, 0, 39, 288, 39));
	player1->Add(new ComponentMotion(0, 0, 0, 0));
	player1->Add(new ComponentPlayer());
	engine.AddEntity(player1);


	Entity *player2 = new Entity(); //double _x, double _x_min, double _x_max, double _x_off, double _y, double _y_min, double _y_max, double _y_off)
	player2->Add(new ComponentSprite(Graphics::SPRITE_PLAYER1, 600, 39, 738, -39, 0, 39, 288, 39));
	player2->Add(new ComponentMotion(0, 0, 0, 0));
	player2->Add(new ComponentPlayer());
	engine.AddEntity(player2);
}

void GameSingle::DestroyEntities()
{
	// TODO: Remove and destroy all entities

}
