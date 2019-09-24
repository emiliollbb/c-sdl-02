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
	pong_logic_data->ball.x=game_sdl_data->sdl_display_mode->w/2;
	pong_logic_data->ball.y=game_sdl_data->sdl_display_mode->h/2;
	pong_logic_data->ball.w=BALL_SIZE;
	pong_logic_data->ball.h=BALL_SIZE;

	init_ball(game_sdl_data, pong_logic_data);

	for(i=0; i<PONG_PLAYERS_COUNT; i++) {
		pong_logic_data->players[i].kinematics.ax=0;
		pong_logic_data->players[i].kinematics.ay=0;
		pong_logic_data->players[i].kinematics.vx=0;
		pong_logic_data->players[i].kinematics.vy=0;
		pong_logic_data->players[i].kinematics.y=100;
		pong_logic_data->players[i].kinematics.w=PLAYER_WIDTH;
		pong_logic_data->players[i].kinematics.h=PLAYER_HEIGHT;
		pong_logic_data->players[i].points=0;
	}

	pong_logic_data->players[0].kinematics.x=10;
	pong_logic_data->players[1].kinematics.x=
			game_sdl_data->sdl_display_mode->w-10-PLAYER_WIDTH;

	pong_logic_data->media.number_font=NULL;
	pong_logic_data->media.text_font=NULL;

	// Return pointer to initialized struct
	return pong_logic_data;
}

void load_media(struct sdl_data_struct *game_sdl_data, void *game_logic_data){
	// Game data
	struct pong_data_struct *pong_data = game_logic_data;
	pong_data->media.number_font=TTF_OpenFont("res/DSEG7Classic-Bold.ttf", 50);
	if(pong_data->media.number_font == NULL)
	{
		printf( "Failed to load numeric font! SDL_ttf Error: %s\n", TTF_GetError() );
		exit(-1);
	}

	pong_data->media.text_font=TTF_OpenFont("res/ArcadeClassic.ttf", 160);
	if(pong_data->media.text_font == NULL)
	{
		printf( "Failed to load text font! SDL_ttf Error: %s\n", TTF_GetError() );
		exit(-1);
	}
}

void init_ball(struct sdl_data_struct *game_sdl_data, struct pong_data_struct *pong_data){
	pong_data->ball.vx=10;
	pong_data->ball.vy=10;
	pong_data->ball.x=game_sdl_data->sdl_display_mode->w/2;
	pong_data->ball.y=game_sdl_data->sdl_display_mode->h/2;
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
	// Text buffer
	char buffer[100];
	// Text color
	SDL_Color text_color;

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

	// Draw players counters
	SDL_SetRenderDrawColor(game_sdl_data->sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	text_color.r=255;
	text_color.g=255;
	text_color.b=255;
	text_color.a=0;
	for(i=0; i<PONG_PLAYERS_COUNT; i++) {
		sprintf(buffer, "%02d", pong_data->players[i].points);
		render_text(game_sdl_data->sdl_renderer, text_color,
				pong_data->media.number_font, buffer,
				5+i*game_sdl_data->sdl_display_mode->w/2, 10);
	}

	// Draw ball
	if(!game_sdl_data->game_over)
	{
		sdl_rect.x=pong_data->ball.x;
		sdl_rect.y=pong_data->ball.y;
		sdl_rect.w=BALL_SIZE;
		sdl_rect.h=BALL_SIZE;
		SDL_RenderFillRect(game_sdl_data->sdl_renderer, &sdl_rect);
	}
	// Draw Game Over
	else {
		render_text(game_sdl_data->sdl_renderer, text_color,
				pong_data->media.text_font, "GAME OVER",
				300, game_sdl_data->sdl_display_mode->h/2-80);
	}



	//Update screen
	SDL_RenderPresent(game_sdl_data->sdl_renderer);
}

void update(struct sdl_data_struct *game_sdl_data, void *game_logic_data) {
	// loops index
	int i;
	// Game data
	struct pong_data_struct *pong_data = game_logic_data;
	// Update players position
	for(i=0; i<PONG_PLAYERS_COUNT; i++) {
		update_position(&(pong_data->players[i].kinematics));
	}

	// Update ball
	update_position(&(pong_data->ball));
	check_collisions_ball(game_sdl_data, pong_data);

	// Check Game Over
	for(i=0; i<PONG_PLAYERS_COUNT; i++) {
		if(pong_data->players[i].points>=10)
		{
			game_sdl_data->game_over=1;
		}
	}
}


void check_collisions_ball(struct sdl_data_struct *game_sdl_data, struct pong_data_struct *pong_data) {
	// loops index
	int i;
	// Check collisions players
	for(i=0; i<PONG_PLAYERS_COUNT; i++) {
		if(check_collision(&pong_data->ball, &pong_data->players[i].kinematics))
		{
			pong_data->ball.vx=-1*pong_data->ball.vx;
		}
	}
	// Check collision top and bottom wall
	if(pong_data->ball.y<0 || pong_data->ball.y>game_sdl_data->sdl_display_mode->h)
	{
		pong_data->ball.vy=-1*pong_data->ball.vy;
	}
	// Check collision left wall
	if(pong_data->ball.x<0)
	{
		pong_data->players[1].points++;
		init_ball(game_sdl_data, pong_data);
	}
	// Check collision right wall
	if(pong_data->ball.x>game_sdl_data->sdl_display_mode->w)
	{
		pong_data->players[0].points++;
		init_ball(game_sdl_data, pong_data);
	}
	else if(pong_data->ball.x>game_sdl_data->sdl_display_mode->w)
	{
		pong_data->ball.vx=-1*pong_data->ball.vx;
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
	else if( e->type == SDL_JOYBUTTONDOWN)
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
