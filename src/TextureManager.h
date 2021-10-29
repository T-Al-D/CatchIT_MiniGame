#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

using std::string;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static SDL_Texture* load_texture(string file_name);
};