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
      auto t = new Tile(Tile::TileType::Rock, *this, x, y);
      _map[y][x] = t;
      _light_map[y][x] = Level::LightType::Unseen;
    }
  }
}

void Level::update(Player& player)
{
  updateLightMap(player);
  _monsters.erase( std::remove_if(_monsters.begin(), _monsters.end(), [](const Monster* m) {return m->dead();}), _monsters.end() );
  update_monsters(player);
}

void Level::update_monsters(Player& player)
{
  CommandProcessor cProc;
  for(auto m : _monsters)
  {
    m->update();
    if(m->hasCommands())
      cProc.Process(m->popCommand(), *m);
  }
}

Player* Level::player()
{
  return _player;
}

void Level::set_player(Player* player)
{
  _player = player;
}

void Level::updateLightMap(Player& player)
{
  ShadowCasting caster;
  std::vector<std::vector<float>> newLightMap = caster.calculateFOV(_map, player.x(), player.y(), 10.0f);

   
  resetLightMap();

  for (int y = 0; y < newLightMap.size(); ++y)
  {
    for (int x = 0; x < newLightMap[y].size(); ++x)
    {
      _light_intensity[y][x] = newLightMap[y][x];
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

Level::LightType Level::light_map(int x, int y)
{
  return _light_map[y][x];
}

float Level::light_intensity(int x, int y)
{
  return _light_intensity[y][x];
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
      if(_map[y][x]->tile_type() == typeToLookFor)
        return _map[y][x];
    }
  }
  return nullptr;
}

Tile* Level::getRandomTileOfType(Tile::TileType typeToLookFor)
{
  do
  {
    auto testTile = getRandomTile();
    if(testTile->tile_type() == typeToLookFor)
      return testTile;
  }while(true);
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

std::vector<Monster*> Level::getMonsters()
{
  return _monsters;
}

void Level::addMonster(Monster* monster)
{
  _monsters.push_back(monster);
}

Tile* Level::getRandomTile()
{
  int x = Random::Between(0, Level::LEVEL_WIDTH-1);
  int y = Random::Between(0, Level::LEVEL_HEIGHT-1);

  Tile* foundTile = getTile(x,y);

  return foundTile;
}

Level::~Level()
{
}
