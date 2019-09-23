// Standard Input/Output library
#include <stdio.h>
// Main SDL library
#include <SDL2/SDL.h>
// SDL Fonts library. Used to render text
#include <SDL2/SDL_ttf.h>

#include "main.h"



/**
 * Main Method.
 */
int main(int argc, char *args[]) {
	// Remaining time to display this frame
	int remaining_ticks;

	// SDL Data
	struct sdl_data_struct game_sdl_data;

	// Game Data
	void *game_logic_data;

	// Variable to hold current event
	SDL_Event e;

	// Initialize random generator seed
	srand(time(NULL));

	/** Reset SDL data (Set Everything to 0, null) **/
	reset_sdl_data(&game_sdl_data);

	// Start up SDL and create window
	init_sdl(&game_sdl_data);

	// Init game data
	game_logic_data = init_game(&game_sdl_data);

	load_media(&game_sdl_data, game_logic_data);

	// Main game loop
	while (!game_sdl_data.quit) {
		game_sdl_data.ticks = SDL_GetTicks();
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			process_input(&e, &game_sdl_data, game_logic_data);
		}
		// Update data
		update(&game_sdl_data, game_logic_data);

		// Render
		render(&game_sdl_data, game_logic_data);

		// Fix framerate
		remaining_ticks = game_sdl_data.ticks + game_sdl_data.ticks_per_frame - SDL_GetTicks();
		if(remaining_ticks > 0)
		{
			//remaining = 1;
			SDL_Delay(remaining_ticks);
		}
		else
		{
			printf("Your system is too slow. %d remaining!!!\n", remaining_ticks);
		}
	}

	close_game(game_logic_data);
	close_sdl(&game_sdl_data);
	return 0;
}

void update_position(struct kinematics_struct *kinematics) {
	// Calculate vx
	kinematics->vx=kinematics->vx+kinematics->ax;
	// Calculate vy
	kinematics->vy=kinematics->vy+kinematics->ay;
	// Calculate position x
	kinematics->x=kinematics->x+kinematics->vx;
	// Calculate position y
	kinematics->y=kinematics->y+kinematics->vy;
}

int check_collision(struct kinematics_struct *object_a, struct kinematics_struct *object_b) {
	if(object_a->x>=object_b->x && object_a->x<=object_b->x+object_b->w
			&&  object_a->y>=object_b->y && object_a->y<=object_b->y+object_b->h)
	{
		return 1;
	}
	else {
		return 0;
	}
}

void reset_sdl_data(struct sdl_data_struct *game_sdl_data) {
	// Loop counter
	int i;
	// quit flag
	game_sdl_data->quit = 0;
	// Game Over flag
	game_sdl_data->game_over = 0;
	// SDL Window
	game_sdl_data->sdl_window=NULL;
	game_sdl_data->sdl_renderer=NULL;
	game_sdl_data->sdl_display_mode=NULL;
	for(i=0; i<JOYSTICK_ARRAY_SIZE; i++)
	{
		game_sdl_data->sdl_joysticks[i]=NULL;
	}
}

void render_text(SDL_Renderer* sdl_renderer, SDL_Color textColor, TTF_Font *font, char *text, int x, int y) {
	// SDL Surface
	SDL_Surface *loadedSurface;
	// Text texture
	SDL_Texture* texture;

	//Load image at specified path
	loadedSurface = TTF_RenderText_Solid(font, text, textColor);
	if( loadedSurface == NULL )
	{
		printf( "Unable to render text! SDL_image Error: %s\n", TTF_GetError() );
		exit(-1);
	}
	else
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(sdl_renderer, loadedSurface );
		if(texture == NULL )
		{
			printf( "Unable to create texture! SDL Error: %s\n", SDL_GetError() );
			exit(-1);
		}
		else {
			SDL_Rect number_rect = {x, y, loadedSurface->w, loadedSurface->h};
			SDL_RenderCopy(sdl_renderer, texture, NULL, &number_rect);

			SDL_DestroyTexture(texture);
		}

		// Clean surface
		SDL_FreeSurface( loadedSurface );
	}
}

void init_sdl(struct sdl_data_struct *game_sdl_data) {
	// Loops index
	int i;

	// Calculate ticks_per_frame
	game_sdl_data->ticks_per_frame=1000/FPS;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		exit(-1);
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
			exit(-1);
		}

		//Check for joysticks
		game_sdl_data->num_joysticks = SDL_NumJoysticks();
		if (game_sdl_data->num_joysticks < 1) {
			printf("Warning: No joysticks connected!\n");
		} else {
			printf("%d joysticks connected\n", game_sdl_data->num_joysticks);
			// Init Joysticks array
			for (i = 0; i < game_sdl_data->num_joysticks; i++) {
				// Open joystick
				game_sdl_data->sdl_joysticks[i] = SDL_JoystickOpen(i);
				// If Open joystick failed, show the error and exit
				if (game_sdl_data->sdl_joysticks[i] == NULL) {
					printf(
							"Warning: Unable to open game controller %d! SDL Error: %s\n",
							i, SDL_GetError());
					exit(-1);
				}
			}

		}

		// Get display mode
		game_sdl_data->sdl_display_mode=malloc(sizeof(SDL_DisplayMode));
		if (SDL_GetDesktopDisplayMode(0, game_sdl_data->sdl_display_mode) != 0) {
			printf("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
			exit(-1);
		}

		printf("Window size: %d, %d\n",
				game_sdl_data->sdl_display_mode->w, game_sdl_data->sdl_display_mode->h);

		// Create window fullscreen
		game_sdl_data->sdl_window = SDL_CreateWindow(
				"PONG",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				game_sdl_data->sdl_display_mode->w, game_sdl_data->sdl_display_mode->h,
				SDL_WINDOW_FULLSCREEN);

		if (game_sdl_data->sdl_window == NULL) {
			printf("Window could not be created! SDL Error: %s\n",
					SDL_GetError());
			exit(-1);
		}

		//Create renderer for window
		game_sdl_data->sdl_renderer = SDL_CreateRenderer(game_sdl_data->sdl_window, -1,
				SDL_RENDERER_ACCELERATED);
		if (game_sdl_data->sdl_renderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n",
					SDL_GetError());
			exit(-1);
		}

		//Initialize SDL TTF
		if (TTF_Init() == -1) {
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
					TTF_GetError());
			exit(-1);
		}
	}
}

void close_sdl(struct sdl_data_struct *game_sdl_data)
{
	int i;

	// Close SDL TTF
	TTF_Quit();

	//Destroy renderer
	if(game_sdl_data->sdl_renderer!=NULL)
	{
		SDL_DestroyRenderer(game_sdl_data->sdl_renderer);
		game_sdl_data->sdl_renderer=NULL;
	}

	// Destroy window
	if(game_sdl_data->sdl_window != NULL)
	{
		SDL_DestroyWindow(game_sdl_data->sdl_window);
		game_sdl_data->sdl_window=NULL;
	}

	// Free sdl_display_mode
	free(game_sdl_data->sdl_display_mode);
	game_sdl_data->sdl_display_mode=NULL;

	for(i=0; i<game_sdl_data->num_joysticks; i++)
	{
		SDL_JoystickClose(game_sdl_data->sdl_joysticks[i]);
		game_sdl_data->sdl_joysticks[i]=NULL;
	}

	// Exit SDL
	SDL_Quit();
}
