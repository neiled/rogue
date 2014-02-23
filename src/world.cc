#include "world.h"
#include "levelbuilder.h"
#include "level.h"
#include "player.h"
#include "tile.h"
#include <SDL2/SDL.h>

World::World()
{
}


World::~World()
{
}

void World::init()
{
  SDL_Log("Creating first level");
  Level* firstLevel = new Level(0);
  firstLevel->set_player(&_player);
  SDL_Log("Building first level");
  _builder.buildLevel(*firstLevel, _player);
  SDL_Log("Done.");
  _levels.push_back(firstLevel);
}

void World::updateGraphics()
{
}

void World::update()
{
  _player.level().update(_player);
  checkMoveLevel();
}

Player* World::player()
{
  return &_player;
}

Level& World::getCurrentLevel()
{
  return _player.level();
}

void World::checkMoveLevel()
{
  if(_player.tile()->tile_type() == Tile::TileType::StairsDown)
  {
    int currentDepth = _player.level().depth();
    Level& currentLevel = _player.level();
    currentLevel.set_player(nullptr);
    auto nextLevel = getLevel(currentDepth+1);
    nextLevel->set_player(&_player);
    auto tileUp = nextLevel->tile_of_type(Tile::TileType::StairsUp);
    if(tileUp)
      _player.setCurrentTile(*tileUp);
  }
  else if(_player.tile()->tile_type() == Tile::TileType::StairsUp)
  {
    int currentDepth = _player.level().depth();
    if(currentDepth > 0)
    {
      Level& currentLevel = _player.level();
      currentLevel.set_player(nullptr);      
      
      auto nextLevel = getLevel(currentDepth-1);
      nextLevel->set_player(&_player);      
      auto tileDown = nextLevel->tile_of_type(Tile::TileType::StairsDown);
      if(tileDown)
        _player.setCurrentTile(*tileDown);
    }
  }
}

Level* World::getLevel(int depth)
{
    if(_levels.size() < depth + 1)
    {
      auto newLevel = new Level(depth);
      _builder.buildLevel(*newLevel, _player);
      _levels.push_back(newLevel);
    }

    return _levels[depth];
}
