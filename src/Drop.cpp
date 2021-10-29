#include "Drop.h"
#include "Game.h"

Drop::Drop(string texture_sheet, unsigned short x, unsigned short y, unsigned short h, unsigned short w)
	: GameEntity(texture_sheet, x, y, h, w)
{
}

Drop::~Drop()
{
}

void Drop::update_drop()
{
	if (y_pos > 745)
	{
		Game::drop_not_catched();
		this->set_health(0);
		this->~Drop();
	}
	y_pos = y_pos + 2;
	dest_rectangle.y = y_pos;
}

/* only call this function ONCE or UNDEFINED behavoir starts to happen*/
bool Drop::check_collision(Drop* drop, Player* player)
{
	if (drop != NULL)
	{
		drop->update_drop();

		/* checks if rectangles have intersection*/
		if (SDL_HasIntersection(drop->get_rectangle(), player->get_rectangle()))
		{
			player->set_hits(player->get_hits() + 1);
			drop->set_health(0);
			drop->catched_sound->play();
			drop = NULL;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}