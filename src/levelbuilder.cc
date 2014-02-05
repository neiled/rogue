#include "levelbuilder.h"
#include <random>

LevelBuilder::LevelBuilder()
{
}

void LevelBuilder::buildLevel(Level* level)
{
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(1,100);
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      int dice_roll = distribution(generator);  
      if(dice_roll >= 15)
        level->setType(x, y, Tile::TileType::Floor);
    }
  }
}

LevelBuilder::~LevelBuilder()
{
}

