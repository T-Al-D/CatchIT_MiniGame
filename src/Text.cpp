#include "Text.h"

Text::Text(string path, unsigned short size, string message_text, const SDL_Color color, unsigned short x, unsigned short y)
	: message(message_text), color(color)
{
	TTF_Init();
	text_rectangle.x = x;
	text_rectangle.y = y;
	font = TTF_OpenFont(path.c_str(), size);
}

Text::~Text()
{
}

void Text::display()
{
	/* render text with font*/
	if (font != NULL)
	{
		SDL_Surface* text_surface = TTF_RenderText_Solid(font, message.c_str(), color);
		text_texture = SDL_CreateTextureFromSurface(Game::game_renderer, text_surface);
		text_rectangle.w = text_surface->w;
		text_rectangle.h = text_surface->h;
		SDL_FreeSurface(text_surface);
		SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rectangle.w, &text_rectangle.h);

		/* text_texture is copied to rendering target and then freed*/
		SDL_RenderCopy(Game::game_renderer, text_texture, nullptr, &text_rectangle);
		SDL_DestroyTexture(text_texture);
	}
	else
	{
		printf("Font ERROR : %s", TTF_GetError());
	}
}