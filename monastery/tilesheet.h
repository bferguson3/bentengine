// tilesheet.h

class TileSheet
{
  public:

    TileSheet(const char* src, int tileCtX, int tileCtY, int tileSizeX, int tileSizeY);
    ~TileSheet();

  private:

    SDL_Surface** surfaces;
};
