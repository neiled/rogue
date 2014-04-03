#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include "player.h"
#include "levelbuilder.h"

class Level;

class World
{
public:
  World ();
  virtual ~World ();
  void init();
  void update();
  void updateGraphics();
  Level* current_level();
  Player* player();


private:
  void checkMoveLevel();
  Level* getLevel(int depth);
  
  Player _player;
  std::vector<Level*> _levels;
  LevelBuilder _builder;  
};
#endif
