#pragma once

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Game.h"

using std::cout;
using std::endl;
using std::string;

class Text
{
public:
	Text(string path, unsigned short size, string message_text, SDL_Color color, unsigned short x, unsigned short y);
	~Text();
	void display();
	void set_message(string new_message) { this->message = new_message; }

private:
	string message;
	SDL_Color color;
	SDL_Texture* text_texture;
	SDL_Rect text_rectangle;
	TTF_Font* font;
};
