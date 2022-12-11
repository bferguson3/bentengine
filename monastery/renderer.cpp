//renderer.cpp 
#include <SDL2/SDL.h>
#include "renderer.h"

int SDLEngine::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL2 failed to initialize!\n");
        return false;
    }
    printf("SDL2 initialized OK!\n");
    return true;
}

//constructor
SDLEngine::SDLEngine()
{
    init();
}
