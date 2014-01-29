#include "world.h"


World::World()
{
  _player = new Player();
}


World::~World()
{
}

void World::update()
{
  
}

Player* World::getPlayer()
{
  return _player;
}
