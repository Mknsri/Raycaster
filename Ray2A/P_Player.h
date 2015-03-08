#ifndef P_PLAYER_H
#define P_PLAYER_H

#include <math.h>

#include "U_Vector2.h"
#include "D_Map.h"
#include "U_Constants.h"


extern const int PLAYER_SIZE;
extern const double PLAYER_FOV;

typedef struct Player {
    Vector2 pos;
    double dir;

    int moving;
    int turning;

    double moveSpeed;
    double rotSpeed;
} Player;


void PlayerMove(Player* p);

#endif