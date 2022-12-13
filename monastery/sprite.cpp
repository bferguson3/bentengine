// sprite.cpp

#include "sprite.h"

extern SDLEngine engine;

Sprite::Sprite() { tilesheet = NULL; }

Sprite::Sprite(TileSheet* ts) { tilesheet = ts; }

SDL_Texture* Sprite::GetTile(int i) { return tilesheet->GetTile(i); }

Sprite::~Sprite()
{
    delete tilesheet;
#if DEBUG
    printf("Sprite %p (tilesheet %p) freed.\n", this, tilesheet);
#endif
}

void Sprite::SetTexture(int i) { GameObject::SetTexture(GetTile(i)); }

void Sprite::SetTilesheet(TileSheet* ts) { tilesheet = ts; }