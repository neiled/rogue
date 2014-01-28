#include "levelbuilder.h"

void LevelBuilder::BuildLevel(Level* level)
{
  for (int y = 0; y < 10; ++y)
  {
    for (int x = 0; x < 10; ++x)
    {
      level->SetType(x, y, Tile::TileType::Floor);
    }
  }
}
