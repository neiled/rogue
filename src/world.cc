#include "world.h"

#include "levelbuilder.h"

World::World()
{
  LevelBuilder* builder = new LevelBuilder();
  Level* firstLevel = new Level();

  builder->buildLevel(firstLevel);


  _player = new Player();
  _player->setCurrentTile(firstLevel->getTile(0,0));
}


World::~World()
{
  delete _player;
}

void World::update()
{
  _player->getCurrentLevel()->update(_player);
}

Player* World::getPlayer()
{
  return _player;
}

Level* World::getCurrentLevel()
{
  return _player->getCurrentLevel();
}
