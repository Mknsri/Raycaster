#include "R_Texture.h"

Texture LoadTexture(char* path) {
    Texture tempTexture = { NULL, 0, 0 };
    SDL_Texture* optimizedTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path);

    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else
    {
        //Convert surface to screen format
        optimizedTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (optimizedTexture == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
        }
        else {
            tempTexture.w = loadedSurface->w;
            tempTexture.h = loadedSurface->h;
            tempTexture.tx = optimizedTexture;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }


    return tempTexture;
}

void RenderTexture(Texture* tx, int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = { x, y, tx->w, tx->h };

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(gRenderer, tx->tx, clip, &renderQuad);
}

void RenderWallStrip(Texture* tx, int x, int y, int destY, SDL_Rect* clip) {
    SDL_Rect renderQuad = { x, y, tx->w, tx->h };

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    renderQuad.h = destY;

    SDL_RenderCopy(gRenderer, tx->tx, clip, &renderQuad);
}