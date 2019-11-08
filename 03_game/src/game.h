#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "../../01_pong/src/main.h"

#ifndef PONG_H
#define PONG_H

#define DUCKS_SIZE 20

struct ducks_media_s {

};

struct ducks_game_data_s {
	struct kinematics_struct hunter;
	struct kinematics_struct ducks[DUCKS_SIZE];
	struct ducks_media_s media;
};

#endif
