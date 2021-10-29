#pragma once

#include <iostream>
#include <string>
#include <SDL_main.h>
#include <SDL_mixer.h>

#include "Game.h"

using std::string;

class Sound
{
public:
	Sound(string file_name);
	~Sound();

	void play();

private:
	/* struct sound data: bytelength, volume*/
	Mix_Chunk* mix_chunk = NULL;
};