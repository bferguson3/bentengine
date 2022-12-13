// sprite.h
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "bentgine.h"
#include "renderer.h"
#include "gameobject.h"
#include "tilesheet.h"

class Sprite : public GameObject
{
  public:

    Sprite();
    Sprite(TileSheet* ts);
    ~Sprite();

    SDL_Texture* GetTile(int i);
    void SetTexture(int i);
    void update();
    void SetTilesheet(TileSheet* ts);

  private:

    TileSheet* tilesheet;
};

#endif