#include "renderer.h"

extern SDLEngine engine;

Text::Text(const char* _str, SDL_Rect* _pos)
{
    str = _str;
    // pos = *_pos;
    SetRect(*_pos);

    SDL_Surface* surface = TTF_RenderText_Solid(engine.GetCurrentFont(), _str, clrWhite);
    SetTexture(SDL_CreateTextureFromSurface(engine.GetRenderer(), surface));
    // Creating a texture with a renderer will ALWAYS cause it to be destroyed.
    // free the surface, useless after we make a texture.
    SDL_FreeSurface(surface);

    engine.addDrawable(this);
}

Text::Text(const char* _str, int x, int y, int w, int h)
{
    str = _str;
    SetRect((SDL_Rect){x, y, w, h});

    SDL_Surface* surface = TTF_RenderText_Solid(engine.GetCurrentFont(), _str, clrWhite);
    SetTexture(SDL_CreateTextureFromSurface(engine.GetRenderer(), surface));

    SDL_FreeSurface(surface);

    engine.addDrawable(this);
}

Text::~Text()
{
    // surface is freed on creation and texture is freed on the renderer. just delete the obj.
    delete this;
}

void Text::display()
{
    // simple!
    SDL_RenderCopy(engine.GetRenderer(), GetTexture(), NULL, GetRect());
}