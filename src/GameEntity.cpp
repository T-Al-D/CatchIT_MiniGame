#include "GameEntity.h"

GameEntity::GameEntity(string texture_sheet, unsigned short x, unsigned short y, unsigned short h, unsigned short w)
	: x_pos(x), y_pos(y), object_texture(TextureManager::load_texture(texture_sheet))
{
	/* source Rectangle: size of original picture (x and y already 0)*/
	src_rectangle.h = h;
	src_rectangle.w = w;

	/* destination Rectangle: size of image on window and where it is*/
	dest_rectangle.x = x_pos;
	dest_rectangle.y = y_pos;
	dest_rectangle.h = h;
	dest_rectangle.w = w;
}

GameEntity::~GameEntity()
{
}

void GameEntity::render()
{
	/* add texture to renderer*/
	SDL_RenderCopy(Game::game_renderer, object_texture, &src_rectangle, &dest_rectangle);
}