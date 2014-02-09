#ifndef TILE_H_
#define TILE_H_

class Level;

class Tile
{
  public:
    enum struct TileType {Floor = 0, Rock=1, StairsDown=2, StairsUp=3, Door=4};

    Tile();
    Tile (TileType tileType, Level* level, int x, int y);
    virtual ~Tile ();
    void setTileType(TileType tileType);
    TileType getTileType();
    Level* getLevel();
    int getX();
    int getY();


  private:
    TileType _tileType;
    int _x;
    int _y;
    Level* _level;
};
#endif
