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
    textureMAX = 64;
    textMAX = 64;
    goMAX = 64;
    texturesToRender = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * textureMAX);
    drawableText = (Text**)malloc(sizeof(Text*) * textMAX);
    drawableObjects = (GameObject**)malloc(sizeof(GameObject*) * goMAX);

#if DEBUG
    printf("SDL2 initialized OK!\n");
#endif

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

#if DEBUG
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

int SDLEngine::GetFrame() { return frameCounter; }

void SDLEngine::draw()
{
    // CLS
    SDL_RenderClear(renderer);

    // Layer 0
    for (int i = 0; i < gameObjectCt; i++)
    {
        drawableObjects[i]->draw();
    }
    // Layer 1
    for (int i = 0; i < textObjectCt; i++)
    {
        drawableText[i]->draw();
    }

    // Drawit
    SDL_RenderPresent(renderer);

    frameCounter++;
    if (frameCounter > 60) // TODO: adjust for variable fps
    {
        frameCounter = 0;
    }
}

void SDLEngine::addDrawable(SDL_Texture* tex)
{
    textureCount++;
    if (textureCount > textureMAX)
    {
        textureMAX += 64;
        texturesToRender = (SDL_Texture**)realloc(texturesToRender, sizeof(SDL_Texture*) * textureMAX);
    }
    texturesToRender[textureCount - 1] = tex;
}

void SDLEngine::addDrawable(Text* t)
{
    // printf("%p\n", t);
    textObjectCt++;
    if (textObjectCt > textMAX)
    {
        textMAX += 64;
        drawableText = (Text**)realloc(drawableText, sizeof(Text*) * textMAX);
    }
    drawableText[textObjectCt - 1] = t;
}

void SDLEngine::addDrawable(GameObject* go)
{
    gameObjectCt++;
    if (gameObjectCt > goMAX)
    {
        goMAX += 64;
        drawableObjects = (GameObject**)realloc(go, sizeof(GameObject*) * gameObjectCt);
    }
    drawableObjects[gameObjectCt - 1] = go;
}

SDL_Renderer* SDLEngine::GetRenderer() { return renderer; }

TTF_Font* SDLEngine::GetCurrentFont() { return currentFont; }

float SDLEngine::GetPerfFrequency() { return perfFrequency; }

RGBAMask SDLEngine::getMasks()
{
    RGBAMask m;
    m.rmask = rmask;
    m.gmask = gmask;
    m.bmask = bmask;
    m.amask = amask;
    return m;
}
