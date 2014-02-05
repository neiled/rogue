#include "level.h"

Level::Level()
{
  for (int y = 0; y < LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < LEVEL_WIDTH; ++x)
    {
      Tile* t = new Tile(Tile::TileType::Rock, this, x, y);
      _map[y][x] = t;
    }
  }
}

void Level::update()
{

}


void Level::setType(int x, int y, Tile::TileType tileType)
{
  _map[y][x]->setTileType(tileType);
}

Tile* Level::getTile(int x, int y)
{
  return _map[y][x];
}



Level::~Level()
{
}
