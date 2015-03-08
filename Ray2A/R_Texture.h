#ifndef R_TEXTURE_H
#define R_TEXTURE_H

#include <SDL_image.h>
#include <SDL.h>
#include "R_SDL.h"

typedef struct Texture {

    SDL_Texture* tx;
    int h,w;

} Texture;

Texture LoadTexture(char* path);
void RenderTexture(Texture* tx, int x, int y, SDL_Rect* clip);
void RenderWallStrip(Texture* tx, int x, int y, int destY, SDL_Rect* clip);

#endif