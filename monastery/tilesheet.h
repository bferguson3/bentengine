// tilesheet.h

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
