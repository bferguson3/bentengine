#ifndef __TEXT_H__
#define __TEXT_H__

#include <SDL2/SDL.h>
#include "gameobject.h"

class Text : public GameObject
{
  public:

    Text(const char* _str, SDL_Rect* pos);
    Text(const char* _str, int x, int y, int w, int h);
    ~Text();

  private:

    const char* str;
};

#endif