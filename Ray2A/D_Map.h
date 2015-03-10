#ifndef D_MAP_H
#define D_MAP_H

#include "R_Texture.h"

#define MAP_W 24
#define MAP_H 24

void LoadMapData();

extern int worldMap[MAP_W][MAP_H];
extern int heightMap[MAP_W][MAP_H];
extern Texture wallTexture;

#endif