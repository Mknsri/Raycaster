#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

// Boolean setup 
typedef int bool;
enum { false, true };

// constants
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int GRID_SIZE = 64;
const int PLAYER_SIZE = 32;
const double PLAYER_FOV = (60 * M_PI) / 180;
const double TWOPI = 2 * M_PI;
int DISTANCE_TO_PROJ_PLANE = 0;
double RAY_INCREMENT = 0;

#define MAP_W 24
#define MAP_H 24

const int MINIMAP_POSX = 10;
const int MINIMAP_POSY = 10;
const int MINIMAP_POINT_SIZE = 10;

// Map
int worldMap[MAP_W][MAP_H] =
{        //1, 2, 3, 4, 5, 6, 7 ,8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 
    /*1*/{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    /*2*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*3*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*4*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*5*/{ 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1 },
    /*6*/{ 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*7*/{ 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1 },
    /*8*/{ 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*9*/{ 1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1 },
    /*0*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*1*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*2*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*3*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*4*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*5*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*6*/{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*7*/{ 1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
    /*8*/{ 1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*9*/{ 1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*0*/{ 1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*1*/{ 1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*2*/{ 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*3*/{ 1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    /*4*/{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// Struct
typedef struct Vector2
{
    double x;
    double y;
} Vector2;

typedef struct Player {
    Vector2 pos;
    double dir;

    int moving;
    int turning;

    double moveSpeed;
    double rotSpeed;
} Player;

// SDL
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Event e;

int InitSDL();
void KillSDL();

// Helpers
Vector2 GetMinimapCoords(Vector2 t);

// Drawing
void ClearScreen();
void DrawMinimap(Player *p);
void Draw3D(Player *p);
void DrawLine(Vector2 s, Vector2 e);
void DrawLineOnMinimap(Vector2 s, Vector2 e);
double CastSingleRay(Vector2 startPos, double angle);

// Events
void HandleEvents(SDL_Event* e, int* r, Player* p);
void PlayerMove(Player* p);

// Debug
void RenderAndStop();

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

        while (running) {
            PlayerMove(&player);
            HandleEvents(&e, &running, &player);
            ClearScreen();

            Draw3D(&player);
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
        }
    }

    return error;
}

void ClearScreen() {
    SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(gRenderer);
}

void DrawMinimap(Player* p) {
    // Draw map
    Vector2 miniMapCoords = { 0, 0 };
    for (int x = 0; x < MAP_W; x++) {
        miniMapCoords.x = x;
        for (int y = 0; y < MAP_H; y++) {
            miniMapCoords.y = y;
            if (worldMap[y][x] > 0) {

                SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 255);

                SDL_RenderDrawLine(gRenderer, (int)GetMinimapCoords(miniMapCoords).x,
                    (int)GetMinimapCoords(miniMapCoords).y, (int)GetMinimapCoords(miniMapCoords).x, MAP_H);
                SDL_RenderDrawLine(gRenderer, (int)GetMinimapCoords(miniMapCoords).x,
                    (int)GetMinimapCoords(miniMapCoords).y, MAP_W, (int)GetMinimapCoords(miniMapCoords).y);


                SDL_SetRenderDrawColor(gRenderer, 127, 127, 127, 127);
                
                SDL_Rect pointRect =
                { (int)GetMinimapCoords(miniMapCoords).x, // X
                  (int)GetMinimapCoords(miniMapCoords).y, // Y
                  MINIMAP_POINT_SIZE, MINIMAP_POINT_SIZE }; // Size

                
                SDL_RenderFillRect(gRenderer, &pointRect);
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 255);

        SDL_RenderDrawLine(gRenderer, (int)GetMinimapCoords(miniMapCoords).x,
            (int)GetMinimapCoords(miniMapCoords).y, MAP_W, (int)GetMinimapCoords(miniMapCoords).y);
    }

    // Draw player pos
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 127);

    // recalculate x and y for easier positioning
    Vector2 playerOnMinimap = GetMinimapCoords(p->pos);
    double playerMiniMapDir = p->dir;

    SDL_Rect playerPoint = { playerOnMinimap.x, /* X */ (int)playerOnMinimap.y, /* Y */ 3, 3 /* Size */ };

    SDL_RenderFillRect(gRenderer, &playerPoint);

    // Draw player direction
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 127);
    double dirLenX = playerOnMinimap.x + (cos(playerMiniMapDir) * 10);
    double dirLenY = playerOnMinimap.y + (sin(playerMiniMapDir) * 10);
    SDL_RenderDrawLine(gRenderer, (int)playerOnMinimap.x + 1, (int)playerOnMinimap.y + 1, (int)dirLenX + 1, (int)dirLenY + 1);

}

void Draw3D(Player* p) {
    // Fuck all

    double rayAngle = p->dir - PLAYER_FOV/2;
    double wallHitDist = 0;

    for (int rayScreenPosX = 0; rayScreenPosX < SCREEN_W; rayScreenPosX++) {
        rayAngle = fmod(rayAngle, TWOPI);
        if (rayAngle < 0) {
            rayAngle += TWOPI;
        }

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);

        wallHitDist = CastSingleRay(p->pos, rayAngle);
        rayAngle += RAY_INCREMENT;

        wallHitDist = wallHitDist * cos(p->dir - rayAngle);

        int lineHeight = 1 / wallHitDist * DISTANCE_TO_PROJ_PLANE;
        // calc lowest and highest pixel
        int drawStart = -lineHeight / 2 + SCREEN_H / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }

        int drawEnd = lineHeight / 2 + SCREEN_H / 2;
        if (drawEnd >=  SCREEN_H) {
            drawEnd = SCREEN_H - 1;
        }
        SDL_RenderDrawLine(gRenderer, rayScreenPosX, drawStart, rayScreenPosX, drawEnd);
    }
}
// Cast single ray, returns distance to hit
double CastSingleRay(Vector2 startPos, double angle) {
    Vector2 gridPos = { 0, 0 }; // The grid were checking
    Vector2 stepSize = { 0, 0 };
    Vector2 stepDir = { 0, 0 };
    Vector2 hitGrid = { 0, 0 };

    bool wallHit = false;
   
    double angleCos = cos(angle);
    double angleSin = sin(angle);

    double wallDistance = 0;
    double vWallDistance = 0, hWallDistance = 0; // Temporary vars for holding walldistance
    double dX = 0, dY = 0; // Used for calculating distance

    // Ray direction in Y, up is -1
    if (angle < 0 || angle > M_PI) {
        stepDir.y = -1;
    } else {
        stepDir.y = 1;
    }

    // Ray direction in X
    if (angle > TWOPI * 0.75 || angle < TWOPI * 0.25) {
        stepDir.x = 1;
    } else {
        stepDir.x = -1;
    }

// Check horizontal gridlines
    double slope = angleCos / angleSin;

    wallHit = false;
    stepSize.y = 1;
    stepSize.x = fabs(1 / tan(angle)); 

    if (stepDir.y < 0) {
        gridPos.y = floor(startPos.y);
    } else {
        gridPos.y = ceil(startPos.y);
    }
    gridPos.x = startPos.x + (gridPos.y - startPos.y) * slope;

    while (!wallHit) {
        int mapX = (int)gridPos.x;
        int mapY = (int)gridPos.y;
        if (stepDir.y == -1) {
            mapY--;
        }
        // We hit the edge of the map
        if ((mapX < 0 || mapX > MAP_W) || (mapY < 0 || mapY > MAP_H)) {
            wallHit = true;
        } else if (worldMap[mapY][mapX] > 0) { // We found a wall
            wallHit = true;
        } else {
            gridPos.x += stepSize.x * stepDir.x;
            gridPos.y += stepSize.y * stepDir.y;
        }
    }

    dX = startPos.x - gridPos.x;
    dY = startPos.y - gridPos.y;
    vWallDistance = dX * dX + dY * dY;
    hitGrid = gridPos;

// Check vectical gridlines
    slope = angleSin / angleCos;

    wallHit = false;
    stepSize.y = fabs(tan(angle));
    stepSize.x = 1;

    if (stepDir.x < 0) {
        gridPos.x = floor(startPos.x);
    }
    else {
        gridPos.x = ceil(startPos.x);
    }
    gridPos.y = startPos.y + (gridPos.x - startPos.x) * slope;

    while (!wallHit) {
        int mapX = (int)gridPos.x;
        int mapY = (int)gridPos.y;

        if (stepDir.x == -1) {
            mapX--;
        }
        // We hit the edge of the map
        if ((mapX < 0 || mapX > MAP_W) || (mapY < 0 || mapY > MAP_H)) {
            wallHit = true;
        }
        // We found a wall
        else if (worldMap[mapY][mapX] > 0) {
            wallHit = true;
        }
        else {
            gridPos.x += stepSize.x * stepDir.x;
            gridPos.y += stepSize.y * stepDir.y;
        }
    }


    dX = startPos.x - gridPos.x;
    dY = startPos.y - gridPos.y;
    hWallDistance = dX * dX + dY * dY;

// Figure out which distance is shorter
    if (vWallDistance < hWallDistance) {
        wallDistance = sqrt(vWallDistance);
        SDL_SetRenderDrawColor(gRenderer, 245, 159, 225, 255);
    }
    else {
        SDL_SetRenderDrawColor(gRenderer, 23, 240, 240, 255);
        wallDistance = sqrt(hWallDistance);
        hitGrid = gridPos;
    }


    // DEBUG
    //SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 255);
    DrawLineOnMinimap(startPos, hitGrid);


    return wallDistance;
}

void HandleEvents(SDL_Event* e, int* r, Player* p) {
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

void PlayerMove(Player* p) {
    if (p->moving != 0) {
        double moveStep = p->moving * p->moveSpeed;
        double newX = (p->pos.x + cos(p->dir) * moveStep);
        double newY = (p->pos.y + sin(p->dir) * moveStep);

        // Collision
        if (worldMap[(int)newY][(int)newX] < 1) {
            p->pos.x = newX;
            p->pos.y = newY;
        }
    }

    if (p->turning != 0)
    {
        p->dir += p->turning * p->rotSpeed;
    }

    p->dir = fmod(p->dir, TWOPI);
    if (p->dir < 0) {
        p->dir += TWOPI;
    }
}

void KillSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Quit();
}

// Helpers
Vector2 GetMinimapCoords(Vector2 t) {
    Vector2 tempVec2 = t;
    tempVec2.x = MINIMAP_POSX + (t.x * MINIMAP_POINT_SIZE);
    tempVec2.y = MINIMAP_POSY + (t.y * MINIMAP_POINT_SIZE);

    return tempVec2;
}

void DrawLine(Vector2 s, Vector2 e) {
    SDL_RenderDrawLine(gRenderer, (int)s.x, (int)s.y, (int)e.x, (int)e.y);
}

void DrawLineOnMinimap(Vector2 s, Vector2 e) {
    s = GetMinimapCoords(s);
    e = GetMinimapCoords(e);
    SDL_RenderDrawLine(gRenderer, (int)s.x, (int)s.y, (int)e.x, (int)e.y);
}

// Debug functions
void RenderAndStop() {
    SDL_RenderPresent(gRenderer);
    getchar();
}