#ifndef __TEXT_H__
#define __TEXT_H__

#include <SDL2/SDL.h>

class Text
{
  public:

    Text(const char* str, SDL_Rect* pos);
    ~Text();

    void display();

    const char* str;
    SDL_Rect* pos;
    SDL_Texture* texture;

  private:

    SDL_Surface* surface;
};

#endif