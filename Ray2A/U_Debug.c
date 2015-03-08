#include "U_Debug.h"

void RenderAndStop() {
    SDL_RenderPresent(gRenderer);
    getchar();
}