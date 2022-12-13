// player.cpp
#include "player.h"
#include "gameobject.h"

extern SDLEngine engine;

Player::Player(TileSheet* ts) { SetTilesheet(ts); }

void Player::update()
{
    if (engine.GetFrame() == 30)
    {
        SetTexture(1);
    }
    else if (engine.GetFrame() == 0)
    {
        SetTexture(2);
    }
}

Player::~Player() {}