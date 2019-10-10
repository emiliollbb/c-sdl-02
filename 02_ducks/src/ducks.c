#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
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
		ducks_data->ducks[i].shoot_frame=0;
		ducks_data->ducks[i].kinematics.enabled=1;
	}

	// Init hunter
	ducks_data->hunter.kinematics.enabled = 1;
	ducks_data->hunter.kinematics.h = HUNTER_HEIGHT;
	ducks_data->hunter.kinematics.w = HUNTER_WIDTH;
	ducks_data->hunter.kinematics.x = 0;
	ducks_data->hunter.kinematics.y = game_sdl_data->sdl_display_mode->h - ducks_data->hunter.kinematics.h;

	// Init bullets
	for(i=0; i<BULLETS_SIZE; i++)
	{
		ducks_data->bullets[i].enabled=0;
	}

	return ducks_data;
}

void load_media(struct sdl_data_struct *game_sdl_data, void *game_logic_data){
	// Game data
	struct ducks_game_data_s *ducks_data = game_logic_data;
	// Load Sprites texture
	ducks_data->media.texture_sprites=load_texture("res/duckhunt_sprites.png", game_sdl_data->sdl_renderer);
	// Load Background texture
	ducks_data->media.background=load_texture("res/field.png", game_sdl_data->sdl_renderer);
	// Load firing chunk
	ducks_data->media.fire_sound = Mix_LoadWAV("res/firing.wav");
	// Load text font
	ducks_data->media.text_font=TTF_OpenFont("res/ArcadeClassic.ttf", 160);;
	if(ducks_data->media.text_font == NULL)
	{
		printf( "Failed to load numeric font! SDL_ttf Error: %s\n", TTF_GetError() );
		exit(-1);
	}
}

void close_media(struct sdl_data_struct *game_sdl_data, void *game_logic_data){
	// Game data
	struct ducks_game_data_s *ducks_data = game_logic_data;

	// Free sound effects
	Mix_FreeChunk(ducks_data->media.fire_sound);
	ducks_data->media.fire_sound = NULL;

	// Destroy textures
	SDL_DestroyTexture(ducks_data->media.background);
	ducks_data->media.background = NULL;
	SDL_DestroyTexture(ducks_data->media.texture_sprites);
	ducks_data->media.texture_sprites = NULL;

	// Close Fonts
	TTF_CloseFont(ducks_data->media.text_font);
	ducks_data->media.text_font = NULL;
}

void close_game(void *game_logic_data)
{
	free(game_logic_data);
}

void render(struct sdl_data_struct *game_sdl_data, void *game_logic_data)
{
	int i;
	SDL_Rect sdl_rect, sdl_rect2;
	SDL_Color text_color;
	// Game data
	struct ducks_game_data_s *ducks_data = game_logic_data;

	text_color.r=0;
	text_color.g=0;
	text_color.b=0;
	text_color.a=0;

	//Clear screen 5e91fe
	SDL_SetRenderDrawColor(game_sdl_data->sdl_renderer, 0x5E, 0x91, 0xFE, 0xFF);
	SDL_RenderClear(game_sdl_data->sdl_renderer);

	// Render background
	sdl_rect.x=0;
	sdl_rect.y=0;
	sdl_rect.w=1080;
	sdl_rect.h=720;
	sdl_rect2.x=0;
	sdl_rect2.y=0;
	sdl_rect2.w=1080;
	sdl_rect2.h=720;
	//sdl_rect2.w=game_sdl_data->sdl_display_mode->w;
	//sdl_rect2.h=game_sdl_data->sdl_display_mode->h;
	SDL_RenderCopyEx(game_sdl_data->sdl_renderer, ducks_data->media.background, &sdl_rect,  &sdl_rect2, 0.0, NULL, SDL_FLIP_NONE);

	// Render ducks
	sdl_rect.w=DUCK_WIDTH;
	sdl_rect.h=DUCK_HEIGHT;
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
	sdl_rect2.x=ducks_data->hunter.kinematics.x;
	sdl_rect2.y=ducks_data->hunter.kinematics.y;
	sdl_rect2.w=ducks_data->hunter.kinematics.w;
	sdl_rect2.h=ducks_data->hunter.kinematics.h;
	SDL_RenderCopyEx(game_sdl_data->sdl_renderer, ducks_data->media.texture_sprites, &sdl_rect,  &sdl_rect2, 0.0, NULL, SDL_FLIP_NONE);

	// Render fired bullets
	SDL_SetRenderDrawColor(game_sdl_data->sdl_renderer, 0x00, 0x00, 0x00, 0xFF );
	for(i=0; i<BULLETS_SIZE; i++)
	{
		if(ducks_data->bullets[i].enabled)
		{
			sdl_rect.x=ducks_data->bullets[i].x;
			sdl_rect.y=ducks_data->bullets[i].y;
			sdl_rect.w=FIRED_BULLET_SIZE;
			sdl_rect.h=FIRED_BULLET_SIZE;
			SDL_RenderFillRect(game_sdl_data->sdl_renderer, &sdl_rect);
		}
	}

	// Draw Game Over
	if(game_sdl_data->game_over)
	{
		render_text(game_sdl_data->sdl_renderer, text_color,
				ducks_data->media.text_font, "GAME OVER",
				300, game_sdl_data->sdl_display_mode->h/2-80);
	}

	//Update screen
	SDL_RenderPresent(game_sdl_data->sdl_renderer);
}

void update(struct sdl_data_struct *game_sdl_data, void *game_logic_data) {
	int i, j, all_ducks_disabled;

	// Game data
	struct ducks_game_data_s *ducks_data = game_logic_data;

	// update ducks
	for(i=0; i<DUCKS_SIZE; i++)
	{
		// Disable outscreen ducks right
		if(ducks_data->ducks[i].kinematics.enabled && ducks_data->ducks[i].kinematics.x > game_sdl_data->sdl_display_mode->w)
		{
			ducks_data->ducks[i].kinematics.enabled=0;
		}
		// Disable outscreen ducks down
		if(ducks_data->ducks[i].kinematics.enabled && ducks_data->ducks[i].kinematics.y > game_sdl_data->sdl_display_mode->h)
		{
			ducks_data->ducks[i].kinematics.enabled=0;
		}
		// Shot time
		if(ducks_data->ducks[i].kinematics.enabled && ducks_data->ducks[i].shoot_frame > 0 && game_sdl_data->frame < ducks_data->ducks[i].shoot_frame + DUCK_FREEZE_FRAMES)
		{
			ducks_data->ducks[i].kinematics.vx=0;
			ducks_data->ducks[i].kinematics.vy=0;
		}
		// 50 frames after shot, the ducks falls
		if(ducks_data->ducks[i].kinematics.enabled && ducks_data->ducks[i].shoot_frame > 0 && game_sdl_data->frame > ducks_data->ducks[i].shoot_frame + DUCK_FREEZE_FRAMES)
		{
			ducks_data->ducks[i].kinematics.vx = 0;
			ducks_data->ducks[i].kinematics.vy = 10;
		}

		// Update ducks position
		ducks_data->ducks[i].kinematics.x += ducks_data->ducks[i].kinematics.vx;
		ducks_data->ducks[i].kinematics.y += ducks_data->ducks[i].kinematics.vy;

	}

	// Update bullets
	for(i=0; i<BULLETS_SIZE; i++)
	{
		if(ducks_data->bullets[i].y > game_sdl_data->sdl_display_mode->h
				|| ducks_data->bullets[i].y < 0
				|| ducks_data->bullets[i].x > game_sdl_data->sdl_display_mode->w
				|| ducks_data->bullets[i].x < 0)
		{
			ducks_data->bullets[i].enabled = 0;
		}
		if(ducks_data->bullets[i].enabled)
		{
			ducks_data->bullets[i].x += ducks_data->bullets[i].vx;
			ducks_data->bullets[i].y += ducks_data->bullets[i].vy;
		}
	}

	// Check collisions
	for(i=0; i<BULLETS_SIZE; i++)
	{
		for(j=0; j<DUCKS_SIZE; j++)
		{
			if(ducks_data->ducks[j].shoot_frame == 0
					&& check_collision(&ducks_data->bullets[i], &ducks_data->ducks[j].kinematics))
			{
				ducks_data->ducks[j].shoot_frame=game_sdl_data->frame;
				//hunters[bullets[i].player].score++;
				ducks_data->bullets[i].enabled=0;
			}
		}
	}


	// Check if end of game
	all_ducks_disabled=1;
	for(i=0; i<DUCKS_SIZE; i++)
	{
		if(ducks_data->ducks[i].kinematics.enabled)
		{
			all_ducks_disabled=0;
			break;
		}
	}
	if(all_ducks_disabled)
	{
		game_sdl_data->game_over=1;
	}
}

void process_input(SDL_Event *e, struct sdl_data_struct *game_sdl_data, void *game_logic_data)
{
	// Game data
	struct ducks_game_data_s *ducks_data = game_logic_data;

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
		case 0: ; fire(e->jbutton.which, ducks_data); break;
		case 1: ; fire(e->jbutton.which, ducks_data); break;
		case 2: ; fire(e->jbutton.which, ducks_data); break;
		case 3: ; fire(e->jbutton.which, ducks_data); break;
		case 4: ; fire(e->jbutton.which, ducks_data); break;
		case 5: ; fire(e->jbutton.which, ducks_data); break;
		case 6: ; fire(e->jbutton.which, ducks_data); break;
		case 7: ; fire(e->jbutton.which, ducks_data); break;
		}
	}
}

void fire(int player, struct ducks_game_data_s *ducks_data) {
	int i;
	// Insert bullet in array
	for(i=0; i<BULLETS_SIZE; i++)
	{
		if(!ducks_data->bullets[i].enabled)
		{
			ducks_data->bullets[i].enabled=1;
			ducks_data->bullets[i].y=ducks_data->hunter.kinematics.y;
			ducks_data->bullets[i].x=ducks_data->hunter.kinematics.x + HUNTER_WIDTH;
			ducks_data->bullets[i].vx=SPEED_BULLET*cos(ANGLE_BULLET);
			ducks_data->bullets[i].vy=-1.0*SPEED_BULLET*sin(ANGLE_BULLET);
			Mix_PlayChannel(-1, ducks_data->media.fire_sound, 0);
			break;
		}
	}
}
