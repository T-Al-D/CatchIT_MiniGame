/* this is needed to prevent error LNK2019: unresolved external symbol _SDL_main referenced in function _main_getcmdline */
/* or use SDL_SetMainReady() */
/* entry Point (?)*/
#define SDL_MAIN_HANDLED

/* basic C++ libraries*/
#include <iostream>

/* special libraries*/
#include <SDL.h>
#include <SDL_image.h>

/* other classes*/
#include "Game.h"

/* constant variables */
const unsigned short FPS = 60;
constexpr unsigned short FRAME_DELAY = 1000 / FPS;

/* other non-constant variables*/
Game* game = new Game();
Uint32 frame_start;
Uint32 frame_time;

int main(void)
{
	SDL_SetMainReady();
	game->show_info();
	game->init_game();
	/* main while LOOP, there is where most of the CODE is executed */
	while (game->is_running)
	{
		/* get Time since init SDL in ms*/
		frame_start = SDL_GetTicks();

		/* ROUTINE */
		game->handle_events();
		game->update_game();
		game->render_game();

		/* length of ROUTINE in ms */
		frame_time = SDL_GetTicks() - frame_start;

		/* dealys the frames and creates a smoother run */
		if (FRAME_DELAY > frame_time)
		{
			/* waiting in ms before return*/
			SDL_Delay(FRAME_DELAY - frame_time);
		}
	}
	/* free the HEAP of everything*/
	game->~Game();

	return 0;
}