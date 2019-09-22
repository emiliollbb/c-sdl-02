#ifndef PONG_H
#define PONG_H

#define PONG_PLAYERS_COUNT 2
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 200

struct pong_player {
	struct kinematics_struct kinematics;
};

struct pong_data_struct
{
	struct kinematics_struct ball;
	struct pong_player players[PONG_PLAYERS_COUNT];
};

#endif
