#include "level.h"

Level::Level()
{
  for (int y = 0; y < LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < LEVEL_WIDTH; ++x)
    {
      Tile* t = new Tile(Tile::TileType::Rock);
      _map[y][x] = t;
    }
  }
}

void Level::BuildLevel(LevelBuilder* builder)
{
}

void Level::SetType(int x, int y, Tile::TileType tileType)
{
  _map[y][x]->SetTileType(tileType);
}



Level::~Level()
{
}
