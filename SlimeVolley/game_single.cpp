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

#define START1 150
#define START2 600

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

		// Get the current Allegro event
		ALLEGRO_EVENT event = AllegroLib::Instance().GetCurrentEvent();

		// If event key down, toggle key in context
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			int keycode = event.keyboard.keycode;
			if (keycode == ALLEGRO_KEY_UP || keycode == ALLEGRO_KEY_DOWN || keycode == ALLEGRO_KEY_LEFT || keycode == ALLEGRO_KEY_RIGHT)
			{
				context->ToggleKey(keycode, true);
			}
		}
		// If event key up, untoggle key in context
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			int keycode = event.keyboard.keycode;
			if (keycode == ALLEGRO_KEY_UP || keycode == ALLEGRO_KEY_DOWN || keycode == ALLEGRO_KEY_LEFT || keycode == ALLEGRO_KEY_RIGHT)
			{
				context->ToggleKey(keycode, false);
			}
		}
		// If event timer, update engine
		else if (event.type == ALLEGRO_EVENT_TIMER)
		{
			engine.Update();
		}

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
	// Initialize required entities and add them to the engine
	Entity *ball = new Entity();
	ball->Add(new ComponentSprite(Graphics::SPRITE_BALL, 150, 11, 738, -11, 150, 11, 288, 11));
	ball->Add(new ComponentMotion(0, 0, 0, 9.81));
	ball->Add(new ComponentBall());
	engine.AddEntity(ball);

	Entity *player1 = new Entity(); //double _x, double _x_min, double _x_max, double _x_off, double _y, double _y_min, double _y_max, double _y_off)
	player1->Add(new ComponentSprite(Graphics::SPRITE_PLAYER1, START1, 39, 738, -39, COY(0), 39, 288, 39));
	player1->Add(new ComponentMotion(0, 0, 0, 0));
	player1->Add(new ComponentPlayer());
	engine.AddEntity(player1);


	Entity *player2 = new Entity(); //double _x, double _x_min, double _x_max, double _x_off, double _y, double _y_min, double _y_max, double _y_off)
	player2->Add(new ComponentSprite(Graphics::SPRITE_PLAYER2, START2, 39, 738, -39, COY(0), 39, 288, 39));
	player2->Add(new ComponentMotion(0, 0, 0, 0));
	player2->Add(new ComponentPlayer());
	engine.AddEntity(player2);

	Entity *eye1 = new Entity();
	eye1->Add(new ComponentSprite(Graphics::SPRITE_PUPIL, 100, 0, 738, 0, 190, 0, 375, 0));
	engine.AddEntity(eye1);

	Entity *eye2 = new Entity();
	eye2->Add(new ComponentSprite(Graphics::SPRITE_PUPIL, START2 - 53, 0, 738, -5, COY(0) + 15, 0, 375, 5));
	engine.AddEntity(eye2);
	
	// Points for player1
	Entity *point11 = new Entity();
	point11->Add(new ComponentSprite(Graphics::SPRITE_POINT, 40, 40));
	point11->Add(new ComponentPoint(1, 1));
	engine.AddEntity(point11);

	Entity *point12 = new Entity();
	point12->Add(new ComponentSprite(Graphics::SPRITE_POINT, 80, 40));
	point12->Add(new ComponentPoint(1, 2));
	engine.AddEntity(point12);

	Entity *point13 = new Entity();
	point13->Add(new ComponentSprite(Graphics::SPRITE_POINT, 120, 40));
	point13->Add(new ComponentPoint(1, 3));
	engine.AddEntity(point13);

	Entity *point14 = new Entity();
	point14->Add(new ComponentSprite(Graphics::SPRITE_POINT, 160, 40));
	point14->Add(new ComponentPoint(1, 4));
	engine.AddEntity(point14);

	Entity *point15 = new Entity();
	point15->Add(new ComponentSprite(Graphics::SPRITE_POINT, 200, 40));
	point15->Add(new ComponentPoint(1, 5));
	engine.AddEntity(point15);

	Entity *point16 = new Entity();
	point16->Add(new ComponentSprite(Graphics::SPRITE_POINT, 240, 40));
	point16->Add(new ComponentPoint(1, 6));
	engine.AddEntity(point16);

	Entity *point17 = new Entity();
	point17->Add(new ComponentSprite(Graphics::SPRITE_POINT, 280, 40));
	point17->Add(new ComponentPoint(1, 7));
	engine.AddEntity(point17);

	// Points for player2
	Entity *point21 = new Entity();
	point21->Add(new ComponentSprite(Graphics::SPRITE_POINT, 469, 40));
	point21->Add(new ComponentPoint(2, 1));
	engine.AddEntity(point21);

	Entity *point22 = new Entity();
	point22->Add(new ComponentSprite(Graphics::SPRITE_POINT, 509, 40));
	point22->Add(new ComponentPoint(2, 2));
	engine.AddEntity(point22);

	Entity *point23 = new Entity();
	point23->Add(new ComponentSprite(Graphics::SPRITE_POINT, 549, 40));
	point23->Add(new ComponentPoint(2, 3));
	engine.AddEntity(point23);

	Entity *point24 = new Entity();
	point24->Add(new ComponentSprite(Graphics::SPRITE_POINT, 589, 40));
	point24->Add(new ComponentPoint(2, 4));
	engine.AddEntity(point24);

	Entity *point25 = new Entity();
	point25->Add(new ComponentSprite(Graphics::SPRITE_POINT, 629, 40));
	point25->Add(new ComponentPoint(2, 5));
	engine.AddEntity(point25);

	Entity *point26 = new Entity();
	point26->Add(new ComponentSprite(Graphics::SPRITE_POINT, 669, 40));
	point26->Add(new ComponentPoint(2, 6));
	engine.AddEntity(point26);

	Entity *point27 = new Entity();
	point27->Add(new ComponentSprite(Graphics::SPRITE_POINT, 709, 40));
	point27->Add(new ComponentPoint(2, 7));
	engine.AddEntity(point27);
	
	// Net
	Entity *net = new Entity();
	net->Add(new ComponentSprite(Graphics::SPRITE_NET, 369, 300));
	engine.AddEntity(net);
}

void GameSingle::DestroyEntities()
{
	// TODO: Remove and destroy all entities
	vector<Entity*> entities = engine.GetEntities();
	for each (Entity* entity in entities)
	{
		engine.RemoveEntity(entity);
	}
}
