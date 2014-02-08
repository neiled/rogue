#include "level.h"
#include <SDL2/SDL.h>
#include "shadowcasting.h"

Level::Level(int depth)
{
  _depth = depth;
  for (int y = 0; y < LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < LEVEL_WIDTH; ++x)
    {
      Tile* t = new Tile(Tile::TileType::Rock, this, x, y);
      _map[y][x] = t;
      _light_map[y][x] = Level::LightType::Unseen;
    }
  }
}

void Level::update(Player* player)
{
  updateLightMap(player);
}

void Level::updateLightMap(Player* player)
{
  ShadowCasting caster;
  vector<vector<float>> newLightMap = caster.calculateFOV(_map, player->getX(), player->getY(), 100.0f);

   
  resetLightMap();

  for (int y = 0; y < newLightMap.size(); ++y)
  {
    for (int x = 0; x < newLightMap[y].size(); ++x)
    {
      if(newLightMap[y][x] > 0)
      {
        _light_map[y][x] = Level::LightType::Lit;
        SDL_Log("Lightmap: %d,%d = %f", x, y, newLightMap[y][x]);
      }
    }
  }

}

void Level::resetLightMap()
{
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      if(_light_map[y][x] == Level::LightType::Lit)
        _light_map[y][x] = Level::LightType::Unlit;
    }
  }
}

Level::LightType Level::getTileLightMap(int x, int y)
{
  return _light_map[y][x];
}

int Level::getDepth()
{
  return _depth;
}

Tile* Level::getTileOfType(Tile::TileType typeToLookFor)
{
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      if(_map[y][x]->getTileType() == typeToLookFor)
        return _map[y][x];
    }
  }
  SDL_Log("Uh oh...");
  return nullptr;
}


void Level::setType(int x, int y, Tile::TileType tileType)
{
  _map[y][x]->setTileType(tileType);
}

Tile* Level::getTile(int x, int y)
{
  if(x >= Level::LEVEL_WIDTH)
    return nullptr;
  if(x < 0)
    return nullptr;
  if(y >= Level::LEVEL_HEIGHT)
    return nullptr;
  if(y < 0)
    return nullptr;
  return _map[y][x];
}



Level::~Level()
{
}
