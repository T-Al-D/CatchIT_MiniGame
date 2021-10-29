#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

SDL_Texture* TextureManager::load_texture(string file_name)
{
	/* load File */
	SDL_Surface* tmp_surface = IMG_Load(file_name.c_str());

	/* create texture from surface pixels */
	SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(Game::game_renderer, tmp_surface);

	/* "old" surface isn´t needed anymore*/
	SDL_FreeSurface(tmp_surface);
	return sdl_texture;
}