#include <SDL2/SDL_ttf.h>

#ifndef PONG_H
#define PONG_H

#define PONG_PLAYERS_COUNT 2
#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 300
#define BALL_SIZE 20

struct pong_player {
	struct kinematics_struct kinematics;
	int points;
};

struct pong_data_struct
{
	struct kinematics_struct ball;
	struct pong_player players[PONG_PLAYERS_COUNT];
	//Globally used font
	TTF_Font *number_font;
};

void check_collisions_ball(struct sdl_data_struct *game_sdl_data, struct pong_data_struct *pong_data);

void init_ball(struct sdl_data_struct *game_sdl_data, struct pong_data_struct *pong_data);

#endif
