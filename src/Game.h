#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "TextureManager.h"
#include "Text.h"
#include "Sound.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Game
{
public:
	/* static variable makes it easy to be used everywhere */
	static SDL_Renderer* game_renderer;
	static SDL_Window* game_window;
	static SDL_Texture* game_background;
	bool is_running = false;

	Game();
	~Game();

	static void drop_not_catched();
	void init_game();
	void delete_all_global_variables();
	void handle_events();
	void update_game();
	void render_game();
	void show_info();
	void show_result();

private:
	unsigned short level = 1;
	unsigned short current_drop;					/* position in vector */
	unsigned short render_cycles;					/* cycles how much the rendering-function was executed */
	unsigned short spawn_rate = 255;				/* time intervalls of spawning */
	unsigned short needed_hits_for_level_up = 4;
	unsigned short requirement_increase = 2;
};

/* constant global variables*/
const string WINDOW_TITLE = "CatchIT";
const string PATH_PICTURES = "resources/pictures/";
const string PATH_FONTS = "resources/fonts/";
const string PATH_SOUNDS = "resources/sounds/";
const unsigned short WINDOW_SIZE = 820;
const unsigned short DROPS_SIZE = 64;               /* figure image sizes are 64*64 Pixels */
const unsigned short PLAYER_SIZE = 128;             /* figure image sizes are 128*128 Pixels */
const unsigned short FIGURE_MOVEMENT_SPEED = 20;
const unsigned short DROP_AMOUNT = 25;
