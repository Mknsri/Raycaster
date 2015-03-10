#include "R_Raycaster.h"

void DrawWalls(Player* p) {

    double rayAngle = p->dir - PLAYER_FOV / 2;

    for (int rayScreenPosX = 0; rayScreenPosX < SCREEN_W; rayScreenPosX++) {
        WallSegment currentSegment = { 0, 0 }; // Result of raycasting
        rayAngle = fmod(rayAngle, TWOPI);
        if (rayAngle < 0) {
            rayAngle += TWOPI;
        }

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);

        currentSegment = CastSingleRay(p->pos, rayAngle);

        // Correct for fisheye
        currentSegment.dist = currentSegment.dist * cos(p->dir - rayAngle);

        DrawWallSegment(currentSegment, rayScreenPosX);
        
        rayAngle += RAY_INCREMENT;
    }
           
}
// Cast single ray, returns distance to hit
WallSegment CastSingleRay(Vector2 startPos, double angle) {
    Vector2 gridPos = { 0, 0 }; // The grid were checking
    Vector2 stepSize = { 0, 0 };
    Vector2 stepDir = { 0, 0 };
    Vector2 hitGrid = { 0, 0 };

    WallSegment tempSegment = { 0, 0 }; // Holds the distance and texture offset of wallsegment

    boolean wallHit = false;

    double angleCos = cos(angle);
    double angleSin = sin(angle);

    double wallDistance = 0;
    double vWallDistance = 0, hWallDistance = 0; // Temporary vars for holding walldistance
    double dX = 0, dY = 0; // Used for calculating distance

    // Ray direction in Y, up is -1
    if (angle < 0 || angle > M_PI) {
        stepDir.y = -1;
    }
    else {
        stepDir.y = 1;
    }

    // Ray direction in X
    if (angle > TWOPI * 0.75 || angle < TWOPI * 0.25) {
        stepDir.x = 1;
    }
    else {
        stepDir.x = -1;
    }

    // Check horizontal gridlines
    double slope = angleCos / angleSin;

    wallHit = false;
    stepSize.y = 1;
    stepSize.x = fabs(1 / tan(angle));

    if (stepDir.y < 0) {
        gridPos.y = floor(startPos.y);
    }
    else {
        gridPos.y = ceil(startPos.y);
    }
    gridPos.x = startPos.x + (gridPos.y - startPos.y) * slope;

    while (!wallHit) {
        int mapX = (int)gridPos.x;
        int mapY = (int)gridPos.y;
        if (stepDir.y < 0) {
            mapY--;
        }
        // We hit the edge of the map
        if ((mapX < 0 || mapX > MAP_W) || (mapY < 0 || mapY > MAP_H)) {
            wallHit = true;
        }
        else if (worldMap[mapY][mapX] > 0) { // We found a wall
            wallHit = true;
        }
        else {
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

        if (stepDir.x < 0) {
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
        tempSegment.textureOffset = fmod(hitGrid.x, 1);

        // Hitgrid might be off 1 step if dir is -1 in either x or y
        // check for this and correct the grid
        if (stepDir.y < 0) {
            hitGrid.y--;
        }
    }
    else {
        wallDistance = sqrt(hWallDistance);
        hitGrid = gridPos;
        tempSegment.textureOffset = fmod(hitGrid.y, 1);

        if (stepDir.x < 0){
            hitGrid.x--;
        }
    }

    tempSegment.dist = wallDistance;

   
    tempSegment.wallType	= ( worldMap[(int)hitGrid.y][(int)hitGrid.x]) - 1;
    tempSegment.height		= (heightMap[(int)hitGrid.y][(int)hitGrid.x]);

    // Correct wall distance for fisheye
    return tempSegment;
}

void DrawWallSegment(WallSegment s, int segmentPosX) {
    
    int lineHeight = (int)round((1 / s.dist * DISTANCE_TO_PROJ_PLANE));
    int yClip = 0; // Where to clip the texture if over the screen limit

    int drawStart = (SCREEN_H / 2 - lineHeight / 2);
    int drawEnd = drawStart + lineHeight;
    lineHeight = (int)(lineHeight * s.height);
    drawStart = drawEnd - lineHeight;
	if (drawStart < 0) {
		yClip = abs(drawStart);
        drawStart = 0;
    }

    // Only clip the texture in horizontal stripes
    SDL_Rect segmentClip = { 0, 0, 0, 0 };
    segmentClip.x = (int)((128 * s.wallType) + (128 * s.textureOffset));
    segmentClip.y = 0;
    segmentClip.w = 1;
    segmentClip.h = 128;
    
    RenderWallStrip(&wallTexture.tx, segmentPosX, drawStart - yClip, lineHeight, &segmentClip);
}