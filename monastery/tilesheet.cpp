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
    int totalTiles = tileCtY * tileCtX;
    surfaces = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * totalTiles);

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
            int i = (y * tileCtY) + x;
            tslice.x = x * tileSizeX;
            tslice.y = y * tileSizeY;
            surfaces[i] =
                SDL_CreateRGBSurface((Uint32)NULL, tileSizeX, tileSizeY, BPP_32, m.rmask, m.gmask, m.bmask, m.amask);
            SDL_BlitSurface(tileMap, &tslice, surfaces[i], NULL);
        }
    }
    SDL_FreeSurface(tileMap);
}

TileSheet::~TileSheet()
{
    // destructor
    free(surfaces);
#if DEBUG
    printf("Surfaces destroyed, tilemap freed.\n");
#endif
}