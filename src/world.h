#ifndef WORLD_H_
#define WORLD_H_

class Player;

class World
{
public:
  World ();
  virtual ~World ();
  void update();
  Level* getCurrentLevel();

private:
  Player* _player;
};
#endif
