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
    void addDrawable(GameObject* go);

    SDL_Renderer* GetRenderer();
    TTF_Font* GetCurrentFont();
    float GetPerfFrequency();

  private:

    // backend
    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Font* defaultFont;
    TTF_Font* currentFont;

    Uint32 rmask, gmask, bmask, amask;

    // int surfaceCount;
    int textureCount;
    int textObjectCt;
    int gameObjectCt;
    SDL_Texture** texturesToRender;
    Text** drawableText;
    GameObject** drawableObjects;
    int textureMAX;
    int textMAX;
    int goMAX;

    double frameCounter;
    float perfFrequency;

    char* fontPath;

    int init();
};

#endif