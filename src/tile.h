#ifndef TILE_H_
#define TILE_H_


class Tile
{
  public:
    enum class TileType {Wall, Floor, Rock};

    Tile();
    Tile (TileType tileType);
    virtual ~Tile ();


  private:
    TileType _tileType;
};
#endif
