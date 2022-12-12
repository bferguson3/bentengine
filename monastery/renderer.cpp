// renderer.cpp

#include <SDL2/SDL.h>
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
    currentFont = defaultFont;

    // window and renderer
    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window,
                                    &renderer) == -1)
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

    // allocate drawables pointers arrays
    texturesToRender = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 1);
    drawableText = (Text**)malloc(sizeof(Text*) * 1);

    printf("SDL2 initialized OK!\n");

    return true;
}

// constructor
SDLEngine::SDLEngine()
{
    // initialize drawable pointers
    // surfaceCount = 0;
    textureCount = 0;
    textObjectCt = 0;

    // SDL core
    init();

    // Set pixel scaling mode
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH / PIXELSCALE, SCREEN_HEIGHT / PIXELSCALE);
    // Set NEAREST vs LINEAR - doesnt work?
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    // black background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

// destructor
SDLEngine::~SDLEngine()
{
    free(texturesToRender);
    free(drawableText);

    // windows and renderers
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();

#ifdef DEBUG
    printf("Cleanup done.\n");
#endif
}

void SDLEngine::update(bool* quitFlag)
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

    // rendercopy takes a srcrest (null if all) and dstrect (null if stretch to full)
    for (int i = 0; i < textObjectCt; i++)
    {
        drawableText[i]->display();
    }

    // Drawit
    SDL_RenderPresent(renderer);

    frameCounter++;
}

void SDLEngine::addDrawable(SDL_Texture* tex)
{
    textureCount++;
    texturesToRender = (SDL_Texture**)realloc(texturesToRender, sizeof(SDL_Texture*) * textureCount);
    texturesToRender[textureCount - 1] = tex;
}

void SDLEngine::addDrawable(Text* t)
{
    // printf("%p\n", t);
    textObjectCt++;
    drawableText = (Text**)realloc(drawableText, sizeof(Text*) * textObjectCt);
    drawableText[textObjectCt - 1] = t;
}

SDL_Renderer* SDLEngine::GetRenderer()
{
    // get
    return renderer;
}

TTF_Font* SDLEngine::GetCurrentFont() { return currentFont; }

float SDLEngine::GetPerfFrequency() { return perfFrequency; }