#include "world.h"


World::World()
{
  _player = new Player();
}


World::~World()
{
  delete _player;
}

void World::update()
{
  
}

Player* World::getPlayer()
{
  return _player;
}

Level* World::getCurrentLevel()
{
  return _player->getCurrentLevel();
}
