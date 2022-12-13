// tilesheet.h
#ifndef __TILESHEET_H__
#define __TILESHEET_H__

class TileSheet
{
  public:

    TileSheet(const char* src, int tileCtX, int tileCtY, int tileSizeX, int tileSizeY);
    ~TileSheet();

    SDL_Texture* GetTile(int i);

  private:

    int totalTiles;
    SDL_Texture** textures;
};

#endif