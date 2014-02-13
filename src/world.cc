#include "world.h"
#include "levelbuilder.h"
#include "level.h"
#include "player.h"
#include "tile.h"

World::World()
{
  _player = new Player();
  Level* firstLevel = new Level(0);
  //_builder = new LevelBuilder();
  _builder.buildLevel(firstLevel, _player);
  _levels.push_back(firstLevel);
}


World::~World()
{
  delete _player;
}

void World::updateGraphics()
{
}

void World::update()
{
  _player->getCurrentLevel()->update(_player);
  checkMoveLevel();
}

Player* World::getPlayer()
{
  return _player;
}

Level* World::getCurrentLevel()
{
  return _player->getCurrentLevel();
}

void World::checkMoveLevel()
{
  if(_player->getCurrentTile()->getTileType() == Tile::TileType::StairsDown)
  {
    int currentDepth = _player->getCurrentLevel()->getDepth();
    Level* nextLevel = getLevel(currentDepth+1);
    _player->setCurrentTile(nextLevel->getTileOfType(Tile::TileType::StairsUp));
  }
  else if(_player->getCurrentTile()->getTileType() == Tile::TileType::StairsUp)
  {
    int currentDepth = _player->getCurrentLevel()->getDepth();
    if(currentDepth > 0)
    {
      Level* nextLevel = getLevel(currentDepth-1);
      _player->setCurrentTile(nextLevel->getTileOfType(Tile::TileType::StairsDown));
    }
  }
}

Level* World::getLevel(int depth)
{
    if(_levels.size() < depth + 1)
    {
      Level* newLevel = new Level(depth);
      _builder->buildLevel(newLevel, _player);
      _levels.push_back(newLevel);
    }

    return _levels[depth];
}
