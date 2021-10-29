#include "Game.h"
#include "GameEntity.h"
#include "Player.h"
#include "Drop.h"

SDL_Renderer* Game::game_renderer;
SDL_Window* Game::game_window;
SDL_Texture* Game::game_background;
Sound* catched_sound;
Sound* dropped_to_the_ground_sound;
Sound* player_move_sound;
Text* result_text;
Text* tries_text;
Text* level_text;
Text* requirement_text;
Player* player;
vector <Drop*> object_drops;

Game::Game()
{
	int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!SDL_Init(SDL_INIT_EVERYTHING)						     /* basic SDL2 lib */
		|| IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != img_flags    /* init libraries for .jpg and .png */
		|| TTF_Init() != 0								         /* Textfont */
		|| !Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))   /*SDL_mixer : 44100 hz is standard on most systems */
	{
		cout << "ALL SYSTEMS initialized !" << endl;
	}
	else
	{
		/* if something didn´t initialize*/
		printf("SDL2 failed: %s\n", SDL_GetError());
		printf("IMG_Load: %s\n", IMG_GetError());
		printf("Font ERROR : %s", TTF_GetError());
		printf("Mix ERROR : %s", Mix_GetError());
	}

	/* the flag SDL_WINDOW_UTILITY is very important for Windowbar !, create Window and renderer */
	game_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE, WINDOW_SIZE,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_UTILITY);

	/* flags for better performance */
	game_renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

	if (game_renderer)
	{
		/* red, green, blue, alpha  0 to 255*/
		SDL_SetRenderDrawColor(game_renderer, 35, 10, 35, 255);
		cout << "RENDERER created !" << endl;
	}
	/* load background */
	game_background = TextureManager::load_texture(PATH_PICTURES + "backgroundHalloween.png");

	/* better Grafics*/
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	cout << "SDL2 initialized !" << endl;

	/* Program is runnig */
	is_running = true;
}

Game::~Game()
{
	/* delete and close everything */
	cout << "GAME ended !" << endl;
	delete_all_global_variables();
	SDL_DestroyWindow(game_window);
	SDL_DestroyRenderer(game_renderer);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::delete_all_global_variables()
{
	object_drops.clear();
	result_text->~Text();
	tries_text->~Text();
	player->~Player();
	player_move_sound->~Sound();
	catched_sound->~Sound();
	dropped_to_the_ground_sound->~Sound();
}

void  Game::init_game()
{
	/* init Sound AFTER SDL_mixer*/
	player_move_sound = new Sound(PATH_SOUNDS + "move_mod.wav");
	catched_sound = new Sound(PATH_SOUNDS + "catch_sound_mod.wav");
	dropped_to_the_ground_sound = new Sound(PATH_SOUNDS + "dropped_to_the_ground_mod.wav");;

	/* objects with texture or pictures*/
	player = new Player(PATH_PICTURES + "bigBasket.png", 350, WINDOW_SIZE - PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE);
	player->set_health(4);

	/* Texts and Fonts*/
	result_text = new Text(PATH_FONTS + "FoundationOne.ttf", 70, "Hits :", { 0, 255,   0, 255 }, 0, 0);
	tries_text = new Text(PATH_FONTS + "GreatVibes-Regular.ttf", 55, "Tries left : 4", { 255, 15, 5, 255 }, 570, 0);

	if (level == 1)
	{
		requirement_text = new Text(PATH_FONTS + "NanumPenScript-Regular.ttf", 42, "Required hits for level UP : 4", { 255, 255, 255, 255 }, WINDOW_SIZE - 465, WINDOW_SIZE - 42);
		level_text = new Text(PATH_FONTS + "DancingScript-Bold.ttf", 40, "Level : 1", { 0, 10, 255, 255 }, 5, WINDOW_SIZE - 45);
	}

	/* for most randomized numbers */
	srand((unsigned int)time(NULL));

	/* fill vector with drops, drops falls from random x location*/
	for (size_t i = 0; i < DROP_AMOUNT; i++)
	{
		Drop* drop = new Drop(PATH_PICTURES + "bonbon.png", rand() % (WINDOW_SIZE - DROPS_SIZE - 10), 0, DROPS_SIZE, DROPS_SIZE);
		drop->set_sound(catched_sound);
		object_drops.push_back(drop);
	}

	current_drop = DROP_AMOUNT - 1;
	render_cycles = 0;
}

void Game::handle_events()
{
	/* if EVENTS are clicked, action happens*/
	SDL_Event sdl_Event;
	SDL_PollEvent(&sdl_Event);
	switch (sdl_Event.type)
	{
	case SDL_QUIT:
		is_running = false;
		break;
	case SDL_KEYDOWN:
		/* if a KEY is pressed*/
		switch (sdl_Event.key.keysym.sym)
		{
		case SDLK_a:
		case SDLK_LEFT:
			if (player->get_x() > 10)
			{
				player->set_x(player->get_x() - FIGURE_MOVEMENT_SPEED);
				player_move_sound->play();
			}
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			if (player->get_x() < (WINDOW_SIZE - PLAYER_SIZE - 10))
			{
				player->set_x(player->get_x() + FIGURE_MOVEMENT_SPEED);
				player_move_sound->play();
			}
			break;
		case SDLK_i:
		case SDLK_p:
			show_info();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Game::update_game()
{
	result_text->set_message("Hits :" + std::to_string(player->get_hits()));

	if (!player->get_health())
	{
		player->set_lost(true);
		show_result();
	}

	if (player->get_hits() == needed_hits_for_level_up)
	{
		show_result();
	}
}

void Game::render_game()
{
	/* clear render buffer */
	SDL_RenderClear(game_renderer);

	/*loading background first!, null for all the frame*/
	SDL_RenderCopy(game_renderer, game_background, NULL, NULL);

	/* add texture to renderer*/
	tries_text->display();
	result_text->display();
	level_text->display();
	requirement_text->display();
	player->render();

	/* drops are keept visible and being updated, as long no collision occurs */
	for (Drop* d : object_drops)
	{
		if (d->get_health() && !(d->check_collision(d, player)))
		{
			d->render();
		}
	}

	/* the spwan rate reglulates when drops become visible and fall*/
	if (!(render_cycles % spawn_rate))
	{
		object_drops[current_drop]->set_health(1);
		current_drop--;
	}
	render_cycles++;

	/* add optics */
	SDL_RenderPresent(game_renderer);
}

/* gets called in the Drop.cpp, if Drop is out of frame*/
void Game::drop_not_catched()
{
	player->set_health(player->get_health() - 1);
	tries_text->set_message("Tries left :" + std::to_string(player->get_health()));
	dropped_to_the_ground_sound->play();
}

void Game::show_info()
{
	/* displays little box with info, game is paused*/
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Welcome to CatchIT!!!",
		"A mini Game made with C++ and SDL2,\n a,d or <- ->  for movements \n i, p for information or pause \n have fun while trying to catch the objects!",
		game_window);
}

/* a more "complex" message_box with options*/
void Game::show_result()
{
	string message;
	if (!player->get_health())
	{
		message = "You have unfortunatley fialed 4 tries\n and therefore you have lost ! \n If you want to leave the Game please EXIT or retry with CONTINE!";
	}
	else
	{
		message = "You have caught the required Objects\n and therefore you have won! \n EXIT OR CONTINE ?";
	}

	if (this->level == 5 && player->get_hits() == needed_hits_for_level_up)
	{
		message = "You have have masterd the final level !\n Congratulations! \n Regardless of what you click next the Game will close. \n Thank you for playing !";
	}

	const SDL_MessageBoxButtonData buttons[] = {
		/* .flags, .buttonid, .text */
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "CONTINUE" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Exit & Close" }
	};

	/* normally you would setup the color, however I didn´t see a difference and therefore simplefied it */
	const SDL_MessageBoxColorScheme colorScheme = { 0
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		game_window,				/* .window */
		"Result, the End",  		/* .title */
		message.c_str(),			/* .message */
		SDL_arraysize(buttons),		/* .numbuttons */
		buttons,					/* .buttons */
		&colorScheme				/* .colorScheme */
	};

	int button_id;
	/* messagebox is shown here, which button was clicked is saved in button_id*/
	if (SDL_ShowMessageBox(&messageboxdata, &button_id) < 0) {
		SDL_Log("ERROR displaying the result message box");
	}

	if (button_id)
	{
		is_running = false;
	}
	else
	{
		if (level == 5 && !(player->get_lost()))
		{
			is_running = false;
		}

		/* delete prevoius values*/
		delete_all_global_variables();
		for (Drop* d : object_drops)
		{
			delete d;
		}
		object_drops.clear();

		/* set new values, depends on win or loss, then give new chance*/
		if (!player->get_lost())
		{
			level++;
			spawn_rate = spawn_rate - 50;
			needed_hits_for_level_up = needed_hits_for_level_up + requirement_increase;
			level_text->set_message("Level :" + std::to_string(level));
			requirement_text->set_message("Required hits for level UP : " + std::to_string(needed_hits_for_level_up));
		}
		player->set_lost(false);
		this->init_game();
	}
}