#include "tile.h"


Tile::Tile()
{
  _tileType = TileType::Rock;
}

Tile::Tile(TileType tileType, int x, int y)
{
  _tileType = tileType;
  _x = x;
  _y = y;
}

Tile::~Tile()
{
}

void Tile::SetTileType(TileType tileType)
{
  _tileType = tileType;
}
