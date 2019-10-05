#include <SDL2/SDL.h>
#include "../../01_pong/src/main.h"
#include "ducks.h"

void* init_game(struct sdl_data_struct *game_sdl_data)
{
	int i;
	struct ducks_game_data_s *ducks_data;
	ducks_data = malloc(sizeof(struct ducks_game_data_s));

	ducks_data->media.texture_sprites=NULL;

	// init ducks
	for(i=0; i<DUCKS_SIZE; i++)
	{
		ducks_data->ducks[i].kinematics.x=DUCK_START_X-300*i-200*(i%2);
		ducks_data->ducks[i].kinematics.y=50+50*(i%2);
		ducks_data->ducks[i].kinematics.w=DUCK_WIDTH;
		ducks_data->ducks[i].kinematics.h=DUCK_HEIGHT;
		ducks_data->ducks[i].kinematics.vx=DUCK_SPEED;
		ducks_data->ducks[i].kinematics.vy=0;
		ducks_data->ducks[i].shoot_time=0;
		ducks_data->ducks[i].kinematics.enabled=1;
	}

	// Init hunter
	ducks_data->hunter.h = HUNTER_HEIGHT;
	ducks_data->hunter.w = HUNTER_WIDTH;
	ducks_data->hunter.x = 0;
	ducks_data->hunter.y = game_sdl_data->sdl_display_mode->h - ducks_data->hunter.h;

	return ducks_data;
}

void load_media(struct sdl_data_struct *game_sdl_data, void *game_logic_data){
	// Game data
	struct ducks_game_data_s *ducks_data = game_logic_data;

	ducks_data->media.texture_sprites=load_texture("res/duckhunt_sprites.png", game_sdl_data->sdl_renderer);
}

void close_game(void *game_logic_data)
{
	free(game_logic_data);
}

void render(struct sdl_data_struct *game_sdl_data, void *game_logic_data)
{
	int i;
	SDL_Rect sdl_rect, sdl_rect2;
	// Game data
	struct ducks_game_data_s *ducks_data = game_logic_data;

	//Clear screen 5e91fe
	SDL_SetRenderDrawColor(game_sdl_data->sdl_renderer, 0x5E, 0x91, 0xFE, 0xFF);
	SDL_RenderClear(game_sdl_data->sdl_renderer);


	// Render ducks
	for(i=0; i<DUCKS_SIZE; i++)
	{
		if(ducks_data->ducks[i].kinematics.enabled)
		{
			if(ducks_data->ducks[i].kinematics.vx!=0 && ducks_data->ducks[i].kinematics.vy==0)
			{
				sdl_rect.x=130+(game_sdl_data->ticks/100%3*40);
				sdl_rect.y=120;
			}
			else if(ducks_data->ducks[i].kinematics.vx==0 && ducks_data->ducks[i].kinematics.vy==0)
			{
				sdl_rect.x=131;
				sdl_rect.y=238;
			}
			else if(ducks_data->ducks[i].kinematics.vx==0 && ducks_data->ducks[i].kinematics.vy>0)
			{
				sdl_rect.x=178;
				sdl_rect.y=237;
			}
			sdl_rect.w=DUCK_WIDTH;
			sdl_rect.h=DUCK_HEIGHT;
			sdl_rect2.x=ducks_data->ducks[i].kinematics.x;
			sdl_rect2.y=ducks_data->ducks[i].kinematics.y;
			sdl_rect2.w=ducks_data->ducks[i].kinematics.w;
			sdl_rect2.h=ducks_data->ducks[i].kinematics.h;
			SDL_RenderCopyEx(game_sdl_data->sdl_renderer, ducks_data->media.texture_sprites, &sdl_rect,  &sdl_rect2, 0.0, NULL, ducks_data->ducks[i].kinematics.vx>0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
		}
	}

	// Render hunter
	sdl_rect.x=HUNTER_X;
	sdl_rect.y=HUNTER_Y;
	sdl_rect.w=HUNTER_WIDTH;
	sdl_rect.h=HUNTER_HEIGHT;
	sdl_rect2.x=ducks_data->hunter.x;
	sdl_rect2.y=ducks_data->hunter.y;
	sdl_rect2.w=ducks_data->hunter.w;
	sdl_rect2.h=ducks_data->hunter.h;
	SDL_RenderCopyEx(game_sdl_data->sdl_renderer, ducks_data->media.texture_sprites, &sdl_rect,  &sdl_rect2, 0.0, NULL, SDL_FLIP_NONE);

	//Update screen
	SDL_RenderPresent(game_sdl_data->sdl_renderer);
}

void update(struct sdl_data_struct *game_sdl_data, void *game_logic_data) {
	int i, j;

	// Game data
	struct ducks_game_data_s *ducks_data = game_logic_data;

	// update ducks
	for(i=0; i<DUCKS_SIZE; i++)
	{
		// Update ducks speed

		// Set speed to 0 to outscreen ducks
		if(ducks_data->ducks[i].kinematics.y>SCREEN_HEIGHT)
		{
			ducks_data->ducks[i].kinematics.enabled=0;
			ducks_data->ducks[i].kinematics.vx=0;
			ducks_data->ducks[i].kinematics.vy=0;
		}
		// Disable outscreen ducks
		if(ducks_data->ducks[i].kinematics.vx>0 && ducks_data->ducks[i].kinematics.x > game_sdl_data->sdl_display_mode->w)
		{
			ducks_data->ducks[i].kinematics.enabled=0;
		}
		// Disable outscreen ducks
		if(ducks_data->ducks[i].kinematics.vx<0 && ducks_data->ducks[i].kinematics.x<0)
		{
			ducks_data->ducks[i].kinematics.enabled=0;
		}
		// Shot time
		if(game_sdl_data->ticks == ducks_data->ducks[i].shoot_time)
		{
			ducks_data->ducks[i].kinematics.vx=0;
			ducks_data->ducks[i].kinematics.vy=0;
		}
		// 10 frames after shot, the ducks falls
		if(ducks_data->ducks[i].shoot_time != 0 && game_sdl_data->ticks == ducks_data->ducks[i].shoot_time+10)
		{
			ducks_data->ducks[i].kinematics.vx=0;
			ducks_data->ducks[i].kinematics.vy=10;
		}

		// Update ducks position
		ducks_data->ducks[i].kinematics.x+=ducks_data->ducks[i].kinematics.vx;
		ducks_data->ducks[i].kinematics.y+=ducks_data->ducks[i].kinematics.vy;

	}
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
