#include "E_Input.h"

void HandleInput(SDL_Event* e, int* r, Player* p) {
    while (SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT)
        {
            *r = 0;
        }

        if (e->type == SDL_KEYDOWN) {
            switch (e->key.keysym.sym)
            {
                case SDLK_UP:
                    p->moving = 1;
                    break;
                case SDLK_DOWN:
                    p->moving = -1;
                    break;
                case SDLK_RIGHT:
                    p->turning = 1;
                    break;
                case SDLK_LEFT:
                    p->turning = -1;
                    break;
                case SDLK_SPACE:
                    break;

                default:
                    break;
            }
        }
        else if (e->type == SDL_KEYUP) {
            switch (e->key.keysym.sym)
            {
                case SDLK_UP:
                case SDLK_DOWN:
                    p->moving = 0;
                    break;
                case SDLK_RIGHT:
                case SDLK_LEFT:
                    p->turning = 0;
                    break;

                case SDLK_PAGEUP:
                    p->dir += 0.1;
                    break;
                case SDLK_PAGEDOWN:
                    p->dir -= 0.1;
            }
        }
    }
}