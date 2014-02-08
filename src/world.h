#ifndef WORLD_H_
#define WORLD_H_

#include "player.h"
#include <vector>

using namespace std;

class Level;
class LevelBuilder;

class World
{
public:
  World ();
  virtual ~World ();
  void update();
  void updateGraphics();
  Level* getCurrentLevel();
  Player* getPlayer();

private:
  Player* _player;
  vector<Level*> _levels;
  LevelBuilder* _builder;
  void checkMoveLevel();
  Level* getLevel(int depth);
};
#endif
