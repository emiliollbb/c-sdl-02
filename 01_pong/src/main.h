// Main SDL library
#include <SDL2/SDL.h>

#ifndef MAIN_H
#define MAIN_H

#define FPS 50
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480
#define JOYSTICK_ARRAY_SIZE 2

struct sdl_data {
	int quit;
	//Screen dimension constants
	int screen_width;
	int screen_height;

	// Clock
	unsigned int ticks;

	// Time to display each frame
	unsigned int ticks_per_frame;

	//The window we'll be rendering to
	SDL_Window *sdl_window;

	//The window renderer
	SDL_Renderer *sdl_renderer;

	// Display mode
	SDL_DisplayMode *sdl_display_mode;

	// Number of joysticks connected
	unsigned int num_joysticks;

	//Game Controller handler
	SDL_Joystick *sdl_joysticks[JOYSTICK_ARRAY_SIZE];
};

void init_sdl(struct sdl_data*);
void reset_sdl_data(struct sdl_data*);
void close_sdl(struct sdl_data*);
void* init_game(struct sdl_data *game_sdl_data);
void close_game(void*);
void render(struct sdl_data*, void*);
void process_input(SDL_Event*, struct sdl_data*, void*);

#endif
