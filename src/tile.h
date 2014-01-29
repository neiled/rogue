#ifndef TILE_H_
#define TILE_H_


class Tile
{
  public:
    enum class TileType {Wall, Floor, Rock};

    Tile();
    Tile (TileType tileType, Level* level, int x, int y);
    virtual ~Tile ();
    void SetTileType(TileType tileType);


  private:
    TileType _tileType;
    int _x;
    int _y;
    Level* _level;
};
#endif
