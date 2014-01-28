#include "tile.h"


Tile::Tile()
{
  _tileType = TileType::Rock;
}

Tile::Tile(TileType tileType)
{
  _tileType = tileType;
}

Tile::~Tile()
{
}
