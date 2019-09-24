// Main SDL library
#include <SDL2/SDL.h>
// SDL Fonts
#include <SDL2/SDL_ttf.h>

#ifndef MAIN_H
#define MAIN_H

#define FPS 50
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480
#define JOYSTICK_ARRAY_SIZE 2

struct sdl_data_struct {
	// Quit flag
	int quit;
	// Game Over flag
	int game_over;

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

struct kinematics_struct
{
	int enabled, x, y, vx, vy, ax, ay, w, h;
};

// Init SDL Engine
void init_sdl(struct sdl_data_struct*);
// Reset SDL data structure
void reset_sdl_data(struct sdl_data_struct*);
// Close SDL Engine
void close_sdl(struct sdl_data_struct*);
// Init game data
void* init_game(struct sdl_data_struct *game_sdl_data);
// Close game data
void close_game(void*);
// Render game screen
void render(struct sdl_data_struct*, void*);
// Handle input events
void process_input(SDL_Event*, struct sdl_data_struct*, void*);
// Update speed and position
void update_position(struct kinematics_struct*);
// Update data
void update(struct sdl_data_struct*, void*);
// Check collisions
int check_collision(struct kinematics_struct*, struct kinematics_struct*);
// Render text
void render_text(SDL_Renderer* sdl_renderer, SDL_Color textColor, TTF_Font *font, char *text, int x, int y);
// Load media
void load_media(struct sdl_data_struct*, void*);
#endif
