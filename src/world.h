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
  void update();
  void updateGraphics();
  Level& getCurrentLevel();
  Player& getPlayer();


private:
  void checkMoveLevel();
  Level* getLevel(int depth);
  
  Player _player;
  std::vector<Level*> _levels;
  LevelBuilder _builder;  
};
#endif
