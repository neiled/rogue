#ifndef WORLD_H_
#define WORLD_H_

class Player;

class World
{
public:
  World ();
  virtual ~World ();
  void update();
  Player* getPlayer();

private:
  Player* _player;
};
#endif
