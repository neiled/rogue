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

void Level::updateLightMap(Player* player)
{
  int maxLightDistance = 5;
  int startLocationX = player->getCurrentTile()->getX() - maxLightDistance;
  int startLocationY = player->getCurrentTile()->getY() - maxLightDistance;
  int endLocationX = player->getCurrentTile()->getX() + maxLightDistance;
  int endLocationY = player->getCurrentTile()->getY() + maxLightDistance;

  if(startLocationX < 0) startLocationX = 0;
  if(startLocationY < 0) startLocationY = 0;
  if(endLocationX >= Level::LEVEL_WIDTH) endLocationX = Level::LEVEL_WIDTH;
  if(endLocationY >= Level::LEVEL_HEIGHT) endLocationY = Level::LEVEL_HEIGHT;

   
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      _light_map[y][x] = false;
    }
  }

  for (int y = startLocationY; y < endLocationY; ++y)
  {
    for (int x = startLocationX; x < endLocationX; ++x)
    {
     _light_map[y][x] = true; 
    }
  }
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
