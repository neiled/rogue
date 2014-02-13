#include "level.h"
#include "player.h"
#include "monster.h"
#include <SDL2/SDL.h>
#include "shadowcasting.h"

Level::Level(int depth)
{
  _depth = depth;
  for (int y = 0; y < LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < LEVEL_WIDTH; ++x)
    {
      auto t = std::make_shared<Tile>(Tile::TileType::Rock, this, x, y);
      _map[y][x] = t;
      _light_map[y][x] = Level::LightType::Unseen;
    }
  }
}

void Level::update(Player* player)
{
  updateLightMap(player);
  _monsters.erase( std::remove_if(_monsters.begin(), _monsters.end(), [](const Monster* m) {return m->dead();}), _monsters.end() );

  //for(Monster* m : _monsters)
  //{
    //if(m->dead())
    //{
      //delete m;
    //}
  //}
}

void Level::updateLightMap(Player* player)
{
  ShadowCasting caster;
  std::vector<std::vector<float>> newLightMap = caster.calculateFOV(_map, player->getX(), player->getY(), 100.0f);

   
  resetLightMap();

  for (int y = 0; y < newLightMap.size(); ++y)
  {
    for (int x = 0; x < newLightMap[y].size(); ++x)
    {
      if(newLightMap[y][x] > 0)
      {
        _light_map[y][x] = Level::LightType::Lit;
        //SDL_Log("Lightmap: %d,%d = %f", x, y, newLightMap[y][x]);
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

std::shared_ptr<Tile> Level::getTileOfType(Tile::TileType typeToLookFor)
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

std::shared_ptr<Tile> Level::getRandomTileOfType(Tile::TileType typeToLookFor)
{
  std::shared_ptr<Tile> chosenTile = nullptr;
  do
  {
    auto testTile = getRandomTile();
    if(testTile->getTileType() == typeToLookFor)
      chosenTile = testTile;
  }while(!chosenTile);
  SDL_Log("Found the tile at %d,%d", chosenTile->getX(), chosenTile->getY());
  return chosenTile;
}

void Level::setType(int x, int y, Tile::TileType tileType)
{
  _map[y][x]->setTileType(tileType);
}

std::shared_ptr<Tile> Level::getTile(int x, int y)
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

std::vector<Monster*> Level::getMonsters()
{
  return _monsters;
}

void Level::addMonster(Monster* monster)
{
  _monsters.push_back(monster);
}

std::shared_ptr<Tile> Level::getRandomTile()
{
  int x = Random::Between(0, Level::LEVEL_WIDTH-1);
  int y = Random::Between(0, Level::LEVEL_HEIGHT-1);

  return getTile(x,y);
}

Level::~Level()
{
}
