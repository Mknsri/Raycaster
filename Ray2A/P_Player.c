#include "P_Player.h"

const int PLAYER_SIZE = 32;
const double PLAYER_FOV = (60 * M_PI) / 180;

void PlayerMove(Player* p) {
    if (p->moving != 0) {
        double moveStep = p->moving * p->moveSpeed;
        double newX = (p->pos.x + cos(p->dir) * moveStep);
        double newY = (p->pos.y + sin(p->dir) * moveStep);

        // Collision
        if (worldMap[(int)newY][(int)newX] < 1) {
            p->pos.x = newX;
            p->pos.y = newY;
        }
    }

    if (p->turning != 0)
    {
        p->dir += p->turning * p->rotSpeed;
    }

    p->dir = fmod(p->dir, TWOPI);
    if (p->dir < 0) {
        p->dir += TWOPI;
    }
}