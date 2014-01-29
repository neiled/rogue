#ifndef WORLD_H_
#define WORLD_H_

#include "player.h"
#include "level.h"

class World
{
public:
  World ();
  virtual ~World ();
  void update();
  Level* getCurrentLevel();
  Player* getPlayer();

private:
  Player* _player;
};
#endif
