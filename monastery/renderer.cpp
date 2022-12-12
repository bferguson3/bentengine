// renderer.cpp
#include "renderer.h"

int SDLEngine::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL2 failed to initialize!\n");
        return false;
    }

    // fonts
    TTF_Init();
    defaultFont = TTF_OpenFont("Bakemono-Stereo-Medium-trial.ttf", 64);
    if (defaultFont == NULL)
        printf("Failed to load font\n");

    // window and renderer
    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
                                    &window, &renderer) == -1)
    {
        printf("Couldn't make window. SDL error: %s\n", SDL_GetError());
        return false;
    }
    // system specific
    perfFrequency = SDL_GetPerformanceFrequency();

// define bitmasking
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    printf("SDL2 initialized OK!\n");
    return true;
}

// constructor
SDLEngine::SDLEngine()
{
    // SDL core
    init();

    // Set pixel scaling mode
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH / PIXELSCALE,
                             SCREEN_HEIGHT / PIXELSCALE);
    // Set NEAREST vs LINEAR - doesnt work?
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    // black background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

// destructor
SDLEngine::~SDLEngine()
{
    // windows and renderers
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    // todo, make this auto
    SDL_DestroyTexture(msgtex);
    // SDL_DestroyTexture(msgtex2);

    SDL_Quit();

#ifdef DEBUG
    printf("Cleanup done.\n");
#endif
}

void SDLEngine::hello()
{
    msg = TTF_RenderText_Solid(defaultFont, "Hello World", clrWhite);
    // msg2 = TTF_RenderText_Solid(defaultFont, "Hello World", clrBlack);

    msgtex = SDL_CreateTextureFromSurface(renderer, msg);
    // msgtex2 = SDL_CreateTextureFromSurface(renderer, msg2);

    SDL_FreeSurface(msg);
    // SDL_FreeSurface(msg2);
}

void SDLEngine::update(bool *quitFlag)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            *quitFlag = true;
    }
}

void SDLEngine::draw()
{
    // CLS
    SDL_RenderClear(renderer);

    // rendercopy takes a srcrest (null if all) and dstrect (null if stretch to
    // full)
    SDL_Rect dst = {0, 0, 100, 25};
    SDL_RenderCopy(renderer, msgtex, NULL, &dst);
    // SDL_RenderCopy(renderer, msgtex2, NULL, NULL);

    // MAP!
    // SDL_RenderCopy(renderer, maptex, &mapCamera, NULL);
    // SDL_RenderCopy(renderer, mapobjtex, &mapCamera, NULL);
    // sel
    // SDL_RenderCopy(renderer, dotSelector, NULL, &mapSelector);

    // Drawit
    SDL_RenderPresent(renderer);
    frameCounter++;
}
