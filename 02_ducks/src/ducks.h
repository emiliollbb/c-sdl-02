#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../01_pong/src/main.h"

#ifndef PONG_H
#define PONG_H

#define DUCKS_SIZE 20
#define DUCK_SPEED 3
#define DUCK_START_X 0
#define DUCK_WIDTH 40
#define DUCK_HEIGHT 30

struct ducks_media_s {
	SDL_Texture *texture_sprites;
};

struct duck_s {
	struct kinematics_struct kinematics;
	unsigned int shoot_time;
};

struct ducks_game_data_s {
	struct kinematics_struct hunter;
	struct duck_s ducks[DUCKS_SIZE];
	struct ducks_media_s media;
};

#endif
