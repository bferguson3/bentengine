// SDL manager class
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "text.h"
#include <SDL2/SDL_ttf.h>
#include "bentgine.h"

const SDL_Color clrWhite = {255, 255, 255, 0};
const SDL_Color clrBlack = {0, 0, 0, 0};

// #define MAXIMUM_ALLOCATED_TEXTURES 1024

class SDLEngine
{
  public:

    SDLEngine();
    ~SDLEngine();

    void update(bool* q);
    void draw();
    void addDrawable(SDL_Texture* tex);
    void addDrawable(Text* t);

    double frameCounter;

    TTF_Font* defaultFont;

    SDL_Renderer* renderer;

  private:

    // backend
    SDL_Window* window;

    float perfFrequency;
    Uint32 rmask, gmask, bmask, amask;

    // int surfaceCount;
    int textureCount;
    int textObjectCt;
    SDL_Texture** texturesToRender;
    Text** drawableText;

    char* fontPath;

    int init();
};

#endif