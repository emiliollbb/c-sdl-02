#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "../../01_pong/src/main.h"

#ifndef PONG_H
#define PONG_H

#define DUCKS_SIZE 20
#define DUCK_SPEED 3
#define DUCK_START_X 0
#define DUCK_WIDTH 40
#define DUCK_HEIGHT 30
#define DUCK_FREEZE_FRAMES 15
#define HUNTER_HEIGHT 196
#define HUNTER_WIDTH 100
#define HUNTER_X 400
#define HUNTER_Y 71
#define BULLETS_SIZE 100
#define FIRED_BULLET_SIZE 4
#define SPEED_BULLET 30.0
#define ANGLE_BULLET 35.0*M_PI/180.0

struct ducks_media_s {
	SDL_Texture *texture_sprites;
	Mix_Chunk *fire_sound;
};

struct duck_s {
	struct kinematics_struct kinematics;
	unsigned int shoot_frame;
};

struct hunter_s {
	struct kinematics_struct kinematics;
};

struct ducks_game_data_s {
	struct hunter_s hunter;
	struct duck_s ducks[DUCKS_SIZE];
	struct kinematics_struct bullets[BULLETS_SIZE];
	struct ducks_media_s media;
};

void fire(int player, struct ducks_game_data_s *ducks_data);

#endif
