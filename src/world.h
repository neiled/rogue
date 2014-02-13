#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

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

  enum class Direction {EAST=0, WEST=1, NORTH=2, SOUTH=3};

private:
  Player* _player;
  std::vector<Level*> _levels;
  LevelBuilder* _builder;
  void checkMoveLevel();
  Level* getLevel(int depth);
};
#endif
