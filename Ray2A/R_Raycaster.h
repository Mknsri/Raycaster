#ifndef R_RAYCASTER_H
#define R_RAYCASTER_H

#include <math.h>

#include "U_Boolean.h"
#include "U_Vector2.h"

#include "R_SDL.h"
#include "R_Minimap.h"
#include "R_Texture.h"

#include "D_Map.h"
#include "P_Player.h"
#include "U_Constants.h"

#include "U_Debug.h"

typedef struct WallSegment {
    double dist;
    double textureOffset;
    double height;
    int wallType;
} WallSegment;

void DrawWalls(Player *p);
void DrawWallSegment(WallSegment s, int segmentPosX);
WallSegment CastSingleRay(Vector2 startPos, double angle);

#endif