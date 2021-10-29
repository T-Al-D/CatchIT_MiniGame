#include "Sound.h"

Sound::Sound(string path)
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	/* loading of data : WAVE, AIFF, RIFF, OGG, or VOC files */
	mix_chunk = Mix_LoadWAV(path.c_str());
}

Sound::~Sound()
{
	/* memory freed in mix_chunk*/
	Mix_FreeChunk(mix_chunk);
}

void Sound::play()
{
	/*-1 random channel, audio data, 0 times in loop*/
	Mix_PlayChannel(-1, mix_chunk, 0);
}