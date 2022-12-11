// SDL manager class 
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "bentgine.h"


const SDL_Color clrWhite = { 255, 255, 255, 0 };
const SDL_Color clrBlack = { 0, 0, 0, 0 };


class SDLEngine
{
    public:
        SDLEngine();
        ~SDLEngine();

        void hello();
        
        void update(bool* q);
        void draw();

        double frameCounter;


    private:
        // backend
        SDL_Window* window;
        SDL_Renderer* renderer;

        float perfFrequency;
        Uint32 rmask, gmask, bmask, amask;

        SDL_Surface* msg;
        SDL_Surface* msg2;
        SDL_Texture* msgtex;
        SDL_Texture* msgtex2;

        TTF_Font* defaultFont;
        char* fontPath;
        
	    int init();
};


#endif 