#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
#include "TextureManager.h"

using std::string;

class GameEntity
{
public:
	GameEntity(string texture_sheet, unsigned short x, unsigned short y, unsigned short h, unsigned short w);
	~GameEntity();

	void render();
	void set_x(unsigned short newX) { this->dest_rectangle.x = newX; }
	void set_y(unsigned short newY) { this->dest_rectangle.y = newY; }
	void set_health(unsigned short new_health) { this->health = new_health; }
	unsigned short get_x() const { return dest_rectangle.x; }
	unsigned short get_y() const { return dest_rectangle.y; }
	unsigned short get_health() const { return health; }
	SDL_Rect* get_rectangle() { return &(this->dest_rectangle); }

protected:
	unsigned short x_pos, y_pos;
	unsigned short health = 0;
	SDL_Texture* object_texture;
	SDL_Rect src_rectangle, dest_rectangle = { 0, 0, 0, 0 };
};