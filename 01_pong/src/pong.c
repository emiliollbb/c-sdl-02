#include <SDL2/SDL.h>
#include "main.h"
#include "pong.h"

void* init_game(struct sdl_data *game_sdl_data)
{
	// Pointer to game logic struct
	struct pong_logic_data_s *pong_logic_data;
	// Initialize memory for game logic struct
	pong_logic_data = malloc(sizeof(struct pong_logic_data_s));
	// Return pointer to initialized struct
	return pong_logic_data;
}

void close_game(void *game_logic_data)
{
	free(game_logic_data);
}

void render(struct sdl_data *game_sdl_data, void *game_logic_data)
{

	//Clear screen
	SDL_SetRenderDrawColor(game_sdl_data->sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(game_sdl_data->sdl_renderer);


	//Update screen
	SDL_RenderPresent(game_sdl_data->sdl_renderer);
}

void process_input(SDL_Event *e, struct sdl_data *game_sdl_data, void *game_logic_data)
{
	//User requests quit
	if(e->type == SDL_QUIT
			// User press ESC or q
			|| (e->type == SDL_KEYDOWN && (e->key.keysym.sym=='q' || e->key.keysym.sym == 27))
			// User 1 press select
			|| (e->type == SDL_JOYBUTTONDOWN && e->jbutton.which==0 && e->jbutton.button == 8))
	{
		game_sdl_data->quit = 1;
	}
}
