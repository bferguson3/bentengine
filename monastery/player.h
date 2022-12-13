// player.h

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "sprite.h"

class Player : public Sprite
{
  public:

    Player();
    Player(TileSheet* ts);
    ~Player();

    void update();

  private:
};

#endif