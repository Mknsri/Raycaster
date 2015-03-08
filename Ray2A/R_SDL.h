#ifndef R_SDL_H
#define R_SDL_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "U_Constants.h"

extern SDL_Surface* gScreenSurface;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Event e;

int InitSDL();
void KillSDL();
void ClearScreen();

#endif