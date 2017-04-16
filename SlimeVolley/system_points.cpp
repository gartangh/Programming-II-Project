#include "system_points.h"

#include "component_point.h"
#include "component_sprite.h"
#include "engine.h"
#include "entity.h"
#include "tags.h"
#include "graphics.h"

void SystemPoints::Update()
{
	// Set the correct sprites of all entities with point component
	// Get current points of player_1 & player_2
	int points_player_1 = engine->GetContext()->GetPoints(1);
	int points_player_2 = engine->GetContext()->GetPoints(2);

	ComponentSprite *comp_sprite_1_1;
	ComponentSprite *comp_sprite_1_2;
	ComponentSprite *comp_sprite_1_3;
	ComponentSprite *comp_sprite_1_4;
	ComponentSprite *comp_sprite_1_5;
	ComponentSprite *comp_sprite_1_6;
	ComponentSprite *comp_sprite_1_7;

	ComponentSprite *comp_sprite_2_1;
	ComponentSprite *comp_sprite_2_2;
	ComponentSprite *comp_sprite_2_3;
	ComponentSprite *comp_sprite_2_4;
	ComponentSprite *comp_sprite_2_5;
	ComponentSprite *comp_sprite_2_6;
	ComponentSprite *comp_sprite_2_7;

	// Get all sprite components corresponding to the right point
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::POINT);
	for each (Entity* entity in entities)
	{
		ComponentPoint *comp_point = (ComponentPoint*)entity->GetComponent(Component::POINT);
		ComponentSprite *comp_sprite = (ComponentSprite*)entity->GetComponent(Component::SPRITE);

		if (comp_point->player_id == 1) {
			switch (comp_point->point_id)
			{
				case 1:
					ComponentSprite *comp_sprite_1_1 = comp_sprite;
					break;
				case 2:
					ComponentSprite *comp_sprite_1_2 = comp_sprite;
					break;
				case 3:
					ComponentSprite *comp_sprite_1_3 = comp_sprite;
					break;
				case 4:
					ComponentSprite *comp_sprite_1_4 = comp_sprite;
					break;
				case 5:
					ComponentSprite *comp_sprite_1_5 = comp_sprite;
					break;
				case 6:
					ComponentSprite *comp_sprite_1_6 = comp_sprite;
					break;
				case 7:
					ComponentSprite *comp_sprite_1_7 = comp_sprite;
					break;
			}
		}

		else if (comp_point->player_id == 2) {
			switch (comp_point->point_id)
			{
			case 1:
				ComponentSprite *comp_sprite_2_1 = comp_sprite;
				break;
			case 2:
				ComponentSprite *comp_sprite_2_2 = comp_sprite;
				break;
			case 3:
				ComponentSprite *comp_sprite_2_3 = comp_sprite;
				break;
			case 4:
				ComponentSprite *comp_sprite_2_4 = comp_sprite;
				break;
			case 5:
				ComponentSprite *comp_sprite_2_5 = comp_sprite;
				break;
			case 6:
				ComponentSprite *comp_sprite_2_6 = comp_sprite;
				break;
			case 7:
				ComponentSprite *comp_sprite_2_7 = comp_sprite;
				break;
			}
		}
	}
	
	// Get correct sprite for player_1 if the point is scored
	Graphics::Sprite sprite = Graphics::SPRITE_POINT_P1;

	// Set all sprites for player_1
	switch (points_player_1)
	{
	case 7:
		comp_sprite_1_7->sprite = sprite;
	case 6:
		comp_sprite_1_6->sprite = sprite;
	case 5:
		comp_sprite_1_5->sprite = sprite;
	case 4:
		comp_sprite_1_4->sprite = sprite;
	case 3:
		comp_sprite_1_3->sprite = sprite;
	case 2:
		comp_sprite_1_2->sprite = sprite;
	case 1:
		comp_sprite_1_1->sprite = sprite;
	}
	
	// Get correct sprite for player_2 if the point is scored
	switch (engine->GetContext()->GetLevel)
	{
	case 0:
		sprite = Graphics::SPRITE_POINT_P2;
		break;
	case 1:
		sprite = Graphics::SPRITE_POINT_O1;
		break;
	case 2:
		sprite = Graphics::SPRITE_POINT_O2;
		break;
	case 3:
		sprite = Graphics::SPRITE_POINT_O3;
		break;
	}

	// Set all sprites for player_2
	switch (points_player_2)
	{
	case 1:
		comp_sprite_2_1->sprite = sprite;
	case 2:
		comp_sprite_2_2->sprite = sprite;
	case 3:
		comp_sprite_2_3->sprite = sprite;
	case 4:
		comp_sprite_2_4->sprite = sprite;
	case 5:
		comp_sprite_2_5->sprite = sprite;
	case 6:
		comp_sprite_2_6->sprite = sprite;
	case 7:
		comp_sprite_2_7->sprite = sprite;
	}
}
