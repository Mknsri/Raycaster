#ifndef R_MINIMAP_H
#define R_MINIMAP_H

#include <math.h>

#include "U_Vector2.h"
#include "P_Player.h"
#include "R_SDL.h"
#include "D_Map.h"

extern const int MINIMAP_POSX;
extern const int MINIMAP_POSY;
extern const int MINIMAP_POINT_SIZE;


void DrawMinimap(Player *p);
void DrawLineOnMinimap(Vector2 s, Vector2 e);
Vector2 GetMinimapCoords(Vector2 t);


#endif