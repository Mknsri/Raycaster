#include "R_Minimap.h"

const int MINIMAP_POSX = 10;
const int MINIMAP_POSY = 10;
const int MINIMAP_POINT_SIZE = 10;

void DrawMinimap(Player* p) {
    // Draw map
    Vector2 miniMapCoords = { 0, 0 };

    // Loop through the map array
    for (int x = 0; x < MAP_W; x++) {
        miniMapCoords.x = x;
        for (int y = 0; y < MAP_H; y++) {
            miniMapCoords.y = y;
            if (worldMap[y][x] > 0) {

                // Draw a wallblock
                SDL_SetRenderDrawColor(gRenderer, 127, 127, 127, 127);

                SDL_Rect pointRect =
                { (int)GetMinimapCoords(miniMapCoords).x, // X
                (int)GetMinimapCoords(miniMapCoords).y, // Y
                MINIMAP_POINT_SIZE, MINIMAP_POINT_SIZE }; // Size

                SDL_RenderFillRect(gRenderer, &pointRect);
            }
        }
    }

    // Draw player pos
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 127);

    // recalculate x and y for easier positioning
    Vector2 playerOnMinimap = GetMinimapCoords(p->pos);
    double playerMiniMapDir = p->dir;

    SDL_Rect playerPoint = { (int)playerOnMinimap.x, /* X */ (int)playerOnMinimap.y, /* Y */ 3, 3 /* Size */ };

    SDL_RenderFillRect(gRenderer, &playerPoint);

    // Draw player directionline
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 127);
    double dirLenX = playerOnMinimap.x + (cos(playerMiniMapDir) * 10);
    double dirLenY = playerOnMinimap.y + (sin(playerMiniMapDir) * 10);
    SDL_RenderDrawLine(gRenderer, (int)playerOnMinimap.x + 1, (int)playerOnMinimap.y + 1, (int)dirLenX + 1, (int)dirLenY + 1);

}


// Helpers
Vector2 GetMinimapCoords(Vector2 t) {
    Vector2 tempVec2 = t;
    tempVec2.x = MINIMAP_POSX + (t.x * MINIMAP_POINT_SIZE);
    tempVec2.y = MINIMAP_POSY + (t.y * MINIMAP_POINT_SIZE);

    return tempVec2;
}



void DrawLineOnMinimap(Vector2 s, Vector2 e) {
    s = GetMinimapCoords(s);
    e = GetMinimapCoords(e);
    SDL_RenderDrawLine(gRenderer, (int)s.x, (int)s.y, (int)e.x, (int)e.y);
}
