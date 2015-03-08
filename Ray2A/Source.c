#include <SDL.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#include "U_Boolean.h"
#include "U_Constants.h"
#include "U_Vector2.h"

#include "P_Player.h"
#include "E_Input.h"

#include "R_SDL.h"
#include "R_Raycaster.h"
#include "R_Minimap.h"
#include "R_Texture.h"



int main(int argc, char* args[]) {
    DISTANCE_TO_PROJ_PLANE = (int)((SCREEN_W / 2) / tan(PLAYER_FOV / 2));
    RAY_INCREMENT = PLAYER_FOV / SCREEN_W;

    if (InitSDL()) {

        // Starting variables
        Player player = { .pos = { 11, 12 }, .dir = 0, .moveSpeed = 0.05, .rotSpeed = 2 * M_PI / 180 };

        int running = 1;

        // Timer
        Uint32 oldTime = 0;
        Uint32 time = 0;
        int countedFrames = 0;
        
        LoadMapData();

        while (running) {
            PlayerMove(&player);
            HandleInput(&e, &running, &player);
            ClearScreen();

            DrawWalls(&player);
            DrawMinimap(&player);

            SDL_RenderPresent(gRenderer);

            // FPS calculations

            oldTime = time;
            time = SDL_GetTicks();
            Uint32 timeSinceLastFrame = time - oldTime;
            if (timeSinceLastFrame < 1000 / 60) {
                SDL_Delay(1000 / 60 - timeSinceLastFrame);
            }

        }
    }
    KillSDL();

    return 0;
}



