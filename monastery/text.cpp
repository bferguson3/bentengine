#include "renderer.h"

extern SDLEngine engine;

Text::Text(const char* _str, SDL_Rect* _pos)
{
    str = _str;
    pos = _pos;

    surface = TTF_RenderText_Solid(engine.defaultFont, _str, clrWhite);
    texture = SDL_CreateTextureFromSurface(engine.renderer, surface);

    // Creating a texture with a renderer will ALWAYS cause it to be destroyed.
    // free the surface, useless after we make a texture.
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
    SDL_RenderCopy(engine.renderer, texture, NULL, pos);
}