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

	// Get correct sprite for player_1 & player_2 if the point is scored
	Graphics::Sprite sprite_1 = Graphics::SPRITE_POINT_P1;
	Graphics::Sprite sprite_2;
	switch (engine->GetContext()->GetLevel())
	{
	case 1:
		sprite_2 = Graphics::SPRITE_POINT_O1; // Level 1
		break;
	case 2:
		sprite_2 = Graphics::SPRITE_POINT_O2; // Level 2
		break;
	case 3:
		sprite_2 = Graphics::SPRITE_POINT_O3; // Level 3
		break;
	default:
		sprite_2 = Graphics::SPRITE_POINT_P2; // Multiplayer
	}

	// Get all sprite components corresponding to the right point
	set<Entity*> entities = engine->GetEntityStream()->WithTag(Component::POINT);
	for each (Entity* entity in entities)
	{
		ComponentPoint *comp_point = (ComponentPoint*)entity->GetComponent(Component::POINT);
		ComponentSprite *comp_sprite = (ComponentSprite*)entity->GetComponent(Component::SPRITE);

		if (comp_point->player_id == 1) {
			if (comp_point->point_id <= points_player_1) {
				comp_sprite->sprite = sprite_1;
			}
			else {
				comp_sprite->sprite = Graphics::SPRITE_POINT;
			}
		}
		else if (comp_point->player_id == 2) {
			if (comp_point->point_id <= points_player_2) {
				comp_sprite->sprite = sprite_2;
			}
			else {
			comp_sprite->sprite = Graphics::SPRITE_POINT;
			}
		}
	}
}
