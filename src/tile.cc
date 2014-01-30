#include "tile.h"


Tile::Tile()
{
  _tileType = TileType::Rock;
}

Tile::Tile(TileType tileType, Level* level, int x, int y)
{
  _tileType = tileType;
  _level = level;
  _x = x;
  _y = y;
}

Tile::~Tile()
{
}

void Tile::setTileType(TileType tileType)
{
  _tileType = tileType;
}

Tile::TileType Tile::getTileType()
{
  return _tileType;
}

Level* Tile::getLevel()
{
  return _level;
}
