#include "world.h"
#include "levelbuilder.h"
#include "level.h"
#include "player.h"
#include "tile.h"
#include <SDL2/SDL.h>
#include "item_factory.h"

World::World()
{
}


World::~World()
{
  for(auto level : _levels)
  {
    delete level;
  }

}

int World::width() const
{
  return WORLD_WIDTH;
}

int World::height() const
{
  return WORLD_HEIGHT;
}

void World::init()
{
    SDL_Log("Creating world...");
    _map = _world_builder.build_world(*this);

  SDL_Log("Creating first level");
  Level* firstLevel = new Level(1);
  firstLevel->set_player(&_player);
  SDL_Log("Building first level");
  _levelBuilder.buildLevel(*firstLevel, _player);
  SDL_Log("Done.");
  _levels.push_back(firstLevel);
  _player.weapon(ItemFactory::Build(ItemType::WEAPON, ItemSubtype::WEAPON_KRIS_RUSTED, 1));
  _player.inventory()->add( ItemFactory::Build(ItemType::WAND, ItemSubtype::WAND_FLAME, 1));
}

void World::updateGraphics()
{
}

void World::update()
{
  checkMoveLevel();
  _player.level().update(_player);
}

Player* World::player()
{
  return &_player;
}

Level* World::current_level()
{
  return &_player.level();
}

void World::checkMoveLevel()
{
  if(_player.tile()->tile_type() == TileType::StairsDown)
  {
    int currentDepth = _player.level().depth();
    Level& currentLevel = _player.level();
    currentLevel.set_player(nullptr);
    auto nextLevel = getLevel(currentDepth+1);
    nextLevel->set_player(&_player);
    auto tileUp = nextLevel->tile_of_type(TileType::StairsUp);
    if(tileUp)
      _player.set_tile(*tileUp);
  }
  else if(_player.tile()->tile_type() == TileType::StairsUp)
  {
    int currentDepth = _player.level().depth();
    if(currentDepth > 1)
    {
      Level& currentLevel = _player.level();
      currentLevel.set_player(nullptr);      
      
      auto nextLevel = getLevel(currentDepth-1);
      nextLevel->set_player(&_player);      
      auto tileDown = nextLevel->tile_of_type(TileType::StairsDown);
      if(tileDown)
        _player.set_tile(*tileDown);
    }
  }
}

Level* World::getLevel(int depth)
{
    if(_levels.size() < depth )
    {
      auto newLevel = new Level(depth);
      _levelBuilder.buildLevel(*newLevel, _player);
      _levels.push_back(newLevel);
    }

    return _levels[depth-1];
}

TileType World::tile_type(int x, int y)
{
  double height =  _map[y][x];
  return TileType::Rock;
}

double World::tile_height(int x, int y)
{
    return _map[y][x];
}

double World::tile_min_height()
{
    return _world_builder.min_height();
}

double World::tile_max_height()
{
    return _world_builder.max_height();
}
