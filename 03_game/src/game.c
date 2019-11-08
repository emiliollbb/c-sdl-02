#include <SDL2/SDL.h>
#include "../../01_pong/src/main.h"
#include "game.h"

void* init_game(struct sdl_data_struct *game_sdl_data)
{

}

void load_media(struct sdl_data_struct *game_sdl_data, void *game_logic_data){
}

void close_game(void *game_logic_data)
{

}

void close_media(struct sdl_data_struct *game_sdl_data, void *game_logic_data){
}

void render(struct sdl_data_struct *game_sdl_data, void *game_logic_data)
{
	//Clear screen
	SDL_SetRenderDrawColor(game_sdl_data->sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(game_sdl_data->sdl_renderer);


	//Update screen
	SDL_RenderPresent(game_sdl_data->sdl_renderer);
}

void update(struct sdl_data_struct *game_sdl_data, void *game_logic_data) {
}

void process_input(SDL_Event *e, struct sdl_data_struct *game_sdl_data, void *game_logic_data)
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
	// Axis events
	else if( e->type == SDL_JOYAXISMOTION)
	{
	}
	// Buttons events
	else if( e->type == SDL_JOYBUTTONDOWN)
	{
		//printf("controller: %d button: %d\n",e->jbutton.which, e->jbutton.button);
		switch( e->jbutton.button)
		{
		case 0: ; break;
		case 1: ; break;
		case 2: ; break;
		case 3: ; break;
		case 4: ; break;
		case 5: ; break;
		case 6: ; break;
		case 7: ; break;
		}
	}
}
