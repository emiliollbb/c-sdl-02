#include <SDL2/SDL.h>
#include "main.h"
#include "pong.h"

void* init_game(struct sdl_data_struct *game_sdl_data)
{
	int i;
	// Pointer to game logic struct
	struct pong_data_struct *pong_logic_data;
	// Initialize memory for game logic struct
	pong_logic_data = malloc(sizeof(struct pong_data_struct));

	pong_logic_data->ball.ax=0;
	pong_logic_data->ball.ay=0;
	pong_logic_data->ball.vx=0;
	pong_logic_data->ball.vy=0;
	pong_logic_data->ball.x=100;
	pong_logic_data->ball.y=100;

	for(i=0; i<PONG_PLAYERS_COUNT; i++) {
		pong_logic_data->players[i].kinematics.ax=0;
		pong_logic_data->players[i].kinematics.ay=0;
		pong_logic_data->players[i].kinematics.vx=0;
		pong_logic_data->players[i].kinematics.vy=0;
		pong_logic_data->players[i].kinematics.y=100;
	}

	pong_logic_data->players[0].kinematics.x=10;
	pong_logic_data->players[1].kinematics.x=
			game_sdl_data->sdl_display_mode->w-10-PLAYER_WIDTH;

	// Return pointer to initialized struct
	return pong_logic_data;
}

void close_game(void *game_logic_data)
{
	free(game_logic_data);
}

void render(struct sdl_data_struct *game_sdl_data, void *game_logic_data)
{
	// loops index
	int i;
	// Aux var
	SDL_Rect sdl_rect;
	// Game data
	struct pong_data_struct *pong_data = game_logic_data;

	//Clear screen
	SDL_SetRenderDrawColor(game_sdl_data->sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(game_sdl_data->sdl_renderer);

	// Draw players
	SDL_SetRenderDrawColor(game_sdl_data->sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	for(i=0; i<PONG_PLAYERS_COUNT; i++) {
		sdl_rect.x=pong_data->players[i].kinematics.x;
		sdl_rect.y=pong_data->players[i].kinematics.y;
		sdl_rect.w=PLAYER_WIDTH;
		sdl_rect.h=PLAYER_HEIGHT;
		SDL_RenderFillRect(game_sdl_data->sdl_renderer, &sdl_rect);
	}



	//Update screen
	SDL_RenderPresent(game_sdl_data->sdl_renderer);
}

void update(struct sdl_data_struct *game_sdl_data, void *game_logic_data) {
	// loops index
	int i;
	// Game data
	struct pong_data_struct *pong_data = game_logic_data;
	for(i=0; i<PONG_PLAYERS_COUNT; i++) {
		update_position(&(pong_data->players[i].kinematics));
	}
}

void process_input(SDL_Event *e, struct sdl_data_struct *game_sdl_data, void *game_logic_data)
{
	// Game data
	struct pong_data_struct *pong_data = game_logic_data;

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
		// Eje y
		if(e->jaxis.axis == 1) {
			pong_data->players[e->jaxis.which].kinematics.vy=e->jaxis.value/32767*5;
		}
	}
	// Buttons events
	else if( e->type == SDL_JOYBUTTONDOWN && e->jbutton.button<8)
	{
		//printf("controller: %d button: %d\n",e->jbutton.which, e->jbutton.button);
		switch( e->jbutton.button)
		{
		case 0:
			pong_data->players[e->jbutton.which].kinematics.vy=0;
			pong_data->players[e->jbutton.which].kinematics.y=0;
			break;

		case 1: ; break;
		case 2:
			pong_data->players[e->jbutton.which].kinematics.vy=0;
			pong_data->players[e->jbutton.which].kinematics.y=
					game_sdl_data->sdl_display_mode->h-PLAYER_HEIGHT;
			break;
		case 3: ; break;
		case 4: ; break;
		case 5: ; break;
		case 6: ; break;
		case 7: ; break;
		}
	}
}
