// gameobject.h
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <SDL2/SDL.h>

class GameObject
{
  public:

    GameObject();
    GameObject(SDL_Texture* tex, SDL_Rect pos);
    GameObject(SDL_Texture* tex, int x, int y, int w, int h);
    ~GameObject();

    void SetPos(int x, int y);
    void SetSize(int w, int h);
    void SetRect(SDL_Rect r);
    void SetTexture(SDL_Texture* tex);

    SDL_Rect* GetRect();
    SDL_Texture* GetTexture();

  private:

    SDL_Texture* texture;
    SDL_Rect pos;
};

#endif
