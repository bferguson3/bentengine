// tilesheet.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tilesheet.h"
#include "bentgine.h"
#include "renderer.h"

extern SDLEngine engine;

TileSheet::TileSheet(const char* src, int tileCtX, int tileCtY, int tileSizeX, int tileSizeY)
{
    // constructor
    totalTiles = tileCtY * tileCtX;
    textures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * totalTiles);

    SDL_Surface* tileMap = IMG_Load(src);

    SDL_Rect tslice;
    tslice.x = 0;
    tslice.y = 0;
    tslice.w = tileSizeX;
    tslice.h = tileSizeY;

    RGBAMask m = engine.getMasks();

    for (int y = 0; y < tileCtY; y++)
    {
        for (int x = 0; x < tileCtX; x++)
        {
            // set slice size
            int i = (y * tileCtY) + x;
            tslice.x = x * tileSizeX;
            tslice.y = y * tileSizeY;
            // make blank surface
            SDL_Surface* surf =
                SDL_CreateRGBSurface((Uint32)NULL, tileSizeX, tileSizeY, BPP_32, m.rmask, m.gmask, m.bmask, m.amask);
            // blit slice to surface
            SDL_BlitSurface(tileMap, &tslice, surf, NULL);
            // make texture
            textures[i] = SDL_CreateTextureFromSurface(engine.GetRenderer(), surf);
            // delete surface
            SDL_FreeSurface(surf);
        }
    }
    // delete tilemap surface
    SDL_FreeSurface(tileMap);
}

TileSheet::~TileSheet()
{
    // destructor
    for (int i = 0; i < totalTiles; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }
    free(textures);
#if DEBUG
    printf("Textures destroyed, tilemap freed.\n");
#endif
}

SDL_Texture* TileSheet::GetTile(int i) { return textures[i]; }