#include "R_SDL.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Event e;

int InitSDL() {
    int error = 1;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Could not initialize SDL: %s \n", SDL_GetError());
        error = 0;
    }
    else {
        gWindow = SDL_CreateWindow("Raycast2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Could not create window: %s \n", SDL_GetError());
            error = 0;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Could not create renderer: %s \n", SDL_GetError());
                error = 0;
            }
            else {
                if (!IMG_Init(IMG_INIT_PNG)) {
                    printf("Could not init SDL_Image: %s \n", IMG_GetError());
                    error = 0;
                }
                
            }
        }
    }

    return error;
}

void ClearScreen() {
    SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(gRenderer);
}


void KillSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Quit();
}
