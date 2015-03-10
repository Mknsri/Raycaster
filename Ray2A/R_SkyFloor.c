#include "R_SkyFloor.h"


void DrawSky() {
    SDL_Rect sky = { 0, 0, SCREEN_W, SCREEN_H / 2 };
    SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 255);
    SDL_RenderFillRect(gRenderer, &sky);
}

void DrawFloor() {
    SDL_Rect floor = { 0, SCREEN_H / 2, SCREEN_W, SCREEN_H };
    SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255);
    SDL_RenderFillRect(gRenderer, &floor);
    
}