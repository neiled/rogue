#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

using namespace std;

class Level;
class LevelBuilder;
class Player;

class World
{
public:
  World ();
  virtual ~World ();
  void update();
  void updateGraphics();
  Level* getCurrentLevel();
  Player* getPlayer();

  enum struct Direction {EAST=0, WEST=1, NORTH=2, SOUTH=3};

private:
  Player* _player;
  vector<Level*> _levels;
  LevelBuilder* _builder;
  void checkMoveLevel();
  Level* getLevel(int depth);
};
#endif
