// gameobject.c
#include "gameobject.h"

GameObject::GameObject()
{
    // Constructor
    texture = NULL;
    pos = (SDL_Rect){0, 0, 16, 16};
}

GameObject::~GameObject()
{
    // destructor
    // destroy texture
    SDL_DestroyTexture(texture);
    // set pos to 0
    pos = (SDL_Rect){0, 0, 0, 0};
    delete this;
}

GameObject::GameObject(SDL_Texture* tex, SDL_Rect _pos)
{
    // constructor with texture and position
    texture = tex;
    pos = _pos;
}

GameObject::GameObject(SDL_Texture* tex, int x, int y, int w, int h)
{
    // constructor with texture and position arguments
    texture = tex;
    pos = (SDL_Rect){x, y, w, h};
}

void GameObject::SetPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void GameObject::SetSize(int w, int h)
{
    // change rect 2 and 3
    pos.w = w;
    pos.h = h;
}

void GameObject::SetTexture(SDL_Texture* tex) { texture = tex; }

void GameObject::SetRect(SDL_Rect r) { pos = r; }

SDL_Rect* GameObject::GetRect() { return &pos; }

SDL_Texture* GameObject::GetTexture() { return texture; }